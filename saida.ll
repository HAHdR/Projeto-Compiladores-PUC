; ModuleID = 'meu_compilador_module'
source_filename = "meu_compilador_module"

@0 = private unnamed_addr constant [28 x i8] c"Iniciando o teste avancado\0A\00", align 1
@1 = private unnamed_addr constant [28 x i8] c"Contando dentro do laco...\0A\00", align 1
@2 = private unnamed_addr constant [17 x i8] c"Fim do programa\0A\00", align 1

define i32 @main() {
entry:
  %contador = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 10, ptr %x, align 4
  %printfcall = call i32 (ptr, ...) @printf(ptr @0)
  store i32 0, ptr %contador, align 4
  br label %whilecond

whilecond:                                        ; preds = %whilebody, %entry
  %contador1 = load i32, ptr %contador, align 4
  %lttmp = icmp slt i32 %contador1, 3
  br i1 %lttmp, label %whilebody, label %afterwhile

whilebody:                                        ; preds = %whilecond
  %printfcall2 = call i32 (ptr, ...) @printf(ptr @1)
  %contador3 = load i32, ptr %contador, align 4
  %addtmp = add i32 %contador3, 1
  store i32 %addtmp, ptr %contador, align 4
  br label %whilecond

afterwhile:                                       ; preds = %whilecond
  %printfcall4 = call i32 (ptr, ...) @printf(ptr @2)
  ret i32 0
}

declare i32 @printf(ptr, ...)
