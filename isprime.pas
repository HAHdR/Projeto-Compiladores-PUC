program IsPrime;
var
  n: integer; 
  i: integer;
  is_p: integer;
begin
  n := argv1;
  is_p := 1;
  
  if n < 2 then
    is_p := 0
  else
  begin
    i := 2;
    while i <= (n / 2) do
    begin
      if (n % i) = 0 then
        is_p := 0;
      i := i + 1;
    end;
  end;
  
  if is_p = 1 then
    writeln("1 (True)")
  else
    writeln("0 (False)");
end.
