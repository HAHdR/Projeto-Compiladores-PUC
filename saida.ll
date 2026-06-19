; ModuleID = 'meu_compilador_module'
source_filename = "meu_compilador_module"

@0 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @main() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @0)
  ret i32 0
}

declare i32 @printf(ptr, ...)
