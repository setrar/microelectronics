LIBRARY ieee ;
USE ieee.std_logic_1164.all ;
USE work.components.all ;

ENTITY swap IS
    PORT ( Data      : IN    STD_LOGIC_VECTOR(7 DOWNTO 0) ;
           Resetn, w : IN    STD_LOGIC ;
           Clock     : IN    STD_LOGIC ;
           RinExt    : IN    STD_LOGIC_VECTOR(1 TO 3) ;
           BusWires  : INOUT STD_LOGIC_VECTOR(7 DOWNTO 0) ;
           Done      : OUT   STD_LOGIC ) ;
END swap ;

ARCHITECTURE Behavior OF swap IS
    TYPE State_type IS (A, B, C, D) ;
    SIGNAL y : State_type ;
    SIGNAL RRin, Rin, Rout : STD_LOGIC_VECTOR(1 TO 3) ;
    SIGNAL R1, R2, R3 : STD_LOGIC_VECTOR(7 DOWNTO 0) ;
BEGIN
    PROCESS ( Resetn, Clock )
    BEGIN
        IF Resetn = '0' THEN
            y <= A ;
        ELSIF (Clock'EVENT AND Clock = '1') THEN
            CASE y IS
                WHEN A =>
                    IF w = '1' THEN
                        y <= B ;
                    ELSE
                        y <= A ;
                    END IF ;
                WHEN B =>
                    y <= C ;
                WHEN C =>
                    y <= D ;
                WHEN D =>
                    y <= A ;
            END CASE ;
        END IF ;
    END PROCESS ;

    Rout(2) <= '1' WHEN y = B ELSE '0' ;
    RRin(3) <= '1' WHEN y = B ELSE '0' ;
    Rout(1) <= '1' WHEN y = C ELSE '0' ;
    RRin(2) <= '1' WHEN y = C ELSE '0' ;
    Rout(3) <= '1' WHEN y = D ELSE '0' ;
    RRin(1) <= '1' WHEN y = D ELSE '0' ;
    Done <= '1' WHEN y = D ELSE '0' ;
    
    Rin(1) <= RinExt(1) OR RRin(1) ;
    Rin(2) <= RinExt(2) OR RRin(2) ;
    Rin(3) <= RinExt(3) OR RRin(3) ;

    -- instantiate registers
    reg1: regn PORT MAP ( BusWires, Rin(1), Clock, R1 ) ;
    reg2: regn PORT MAP ( BusWires, Rin(2), Clock, R2 ) ;
    reg3: regn PORT MAP ( BusWires, Rin(3), Clock, R3 ) ;
    -- define the bus
    PROCESS ( y, Data, R1, R2, R3 )
    BEGIN
        IF (y = B) THEN 
            BusWires <= R2 ;
        ELSIF (y = C) THEN 
            BusWires <= R1 ;
        ELSIF (y = D) THEN 
            BusWires <= R3 ;
        ELSE 
            BusWires <= Data ;
        END IF ;
    END PROCESS ;
END Behavior ;
