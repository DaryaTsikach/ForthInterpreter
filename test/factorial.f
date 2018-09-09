: factorial 
	DUP 2 < IF DROP 1 
	ELSE
	DUP
	BEGIN
		1-
		SWAP OVER
		* SWAP
		DUP 1 =
	UNTIL
DROP THEN ;

1 factorial . 
5 factorial .
