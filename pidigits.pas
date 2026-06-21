program PIdigits;
var
  n: integer;
  num: integer;
  den: integer;
  digit: integer;
  i: integer;
begin
  n := argv1;
  num := 355;
  den := 113;
  
  writeln("Digitos de Pi:");
  for i := 1 to n do
  begin
    digit := num / den;
    writeln(digit);
    
    num := (num % den) * 10;
  end;
end.
