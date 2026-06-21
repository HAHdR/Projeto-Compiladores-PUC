program TesteArgv;
var
  n : integer;
begin
  n := argv1;
  write("Voce passou o numero: ");
  writeln(n);
  write("Total de argumentos (argc): ");
  writeln(argc);

  if n > 0 then
    writeln("O numero passado e positivo")
  else
    writeln("Nenhum numero (ou zero/negativo) foi passado");
end.
