program Factor;
var
  n: integer;
  i: integer;
begin
  n := argv1;
  i := 2;
  
  writeln("Fatores primos:");
  while n > 1 do
  begin
    while (n % i) = 0 do
    begin
      writeln(i);
      n := n / i;
    end;
    i := i + 1;
  end;
end.
