ENTITY example2 IS
    PORT ( x1, x2, x3, x4 : IN  BIT ;
           f, g           : OUT BIT ) ;
END example2 ;

ARCHITECTURE LogicFunc OF example2 IS
BEGIN
    f <= (x1 AND x3) OR (x2 AND x4) ;
    g <= (x1 OR NOT x3) AND (NOT x2 OR x4) ;
END LogicFunc ;

