program TesteFor;
var
  i : integer;
  soma : integer;
begin
  soma := 0;
  for i := 1 to 5 do
  begin
    writeln("Iteracao do laco for");
    soma := soma + i;
  end;
  writeln("Fim do teste for");
end.