program TesteFuncoes;
var
  resultado : integer;

function Quadrado(n : integer) : integer;
begin
  Quadrado := n * n;
end;

procedure Saudacao(vezes : integer);
var
  i : integer;
begin
  for i := 1 to vezes do
  begin
    writeln("Ola da funcao Saudacao");
  end;
end;

begin
  resultado := Quadrado(5);
  Saudacao(3);

  if resultado = 25 then
    writeln("Quadrado de 5 calculado corretamente")
  else
    writeln("Erro no calculo do quadrado");
end.
