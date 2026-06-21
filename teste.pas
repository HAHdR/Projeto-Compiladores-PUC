program TesteAvancado;
var
  x : integer;
  contador : integer;
begin
  x := 10;
  writeln("Iniciando o teste avancado");
  
  // Testando a alocacao e o incremento de variaveis num laco
  contador := 0;
  while contador < 3 do
  begin
    writeln("Contando dentro do laco...");
    contador := contador + 1;
  end;
  
  writeln("Fim do programa");
end.