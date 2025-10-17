ENTITY example1 IS
   PORT ( x1, x2, s : IN  BIT ;
          f         : OUT BIT ) ;
END example1 ; 

ARCHITECTURE LogicFunc OF example1 IS 
BEGIN
  f  <= (NOT s AND x1) OR (s AND x2) ; 
END LogicFunc ; 

