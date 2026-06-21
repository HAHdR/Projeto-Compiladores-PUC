program Fibonacci;
var
  n: integer;
  a: integer;
  b: integer;
  temp: integer; 
  i: integer;
begin
  n := argv1;
  a := 0;
  b := 1;
  
  writeln("Fibonacci:");
  for i := 1 to n do
  begin
    writeln(a);
    temp := a + b;
    a := b;
    b := temp;
  end;
end.
