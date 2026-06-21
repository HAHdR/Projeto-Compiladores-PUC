; ModuleID = 'meu_compilador_module'
source_filename = "meu_compilador_module"

@0 = private unnamed_addr constant [23 x i8] c"Voce passou o numero: \00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@3 = private unnamed_addr constant [29 x i8] c"Total de argumentos (argc): \00", align 1
@4 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@5 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@6 = private unnamed_addr constant [28 x i8] c"O numero passado e positivo\00", align 1
@7 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@8 = private unnamed_addr constant [45 x i8] c"Nenhum numero (ou zero/negativo) foi passado\00", align 1
@9 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %n = alloca i32, align 4
  %argc_slot = alloca i32, align 4
  %argv1_slot = alloca i32, align 4
  store i32 %argc, ptr %argc_slot, align 4
  %hasargcond = icmp sgt i32 %argc, 1
  br i1 %hasargcond, label %hasarg, label %noarg

hasarg:                                           ; preds = %entry
  %argv1slot = getelementptr ptr, ptr %argv, i32 1
  %argv1str = load ptr, ptr %argv1slot, align 8
  %argv1int = call i32 @atoi(ptr %argv1str)
  store i32 %argv1int, ptr %argv1_slot, align 4
  br label %argdone

noarg:                                            ; preds = %entry
  store i32 0, ptr %argv1_slot, align 4
  br label %argdone

argdone:                                          ; preds = %noarg, %hasarg
  %argv1 = load i32, ptr %argv1_slot, align 4
  store i32 %argv1, ptr %n, align 4
  %printfcall = call i32 (ptr, ...) @printf(ptr @1, ptr @0)
  %n1 = load i32, ptr %n, align 4
  %printfcall2 = call i32 (ptr, ...) @printf(ptr @2, i32 %n1)
  %printfcall3 = call i32 (ptr, ...) @printf(ptr @4, ptr @3)
  %argc4 = load i32, ptr %argc_slot, align 4
  %printfcall5 = call i32 (ptr, ...) @printf(ptr @5, i32 %argc4)
  %n6 = load i32, ptr %n, align 4
  %gttmp = icmp sgt i32 %n6, 0
  br i1 %gttmp, label %then, label %else

then:                                             ; preds = %argdone
  %printfcall7 = call i32 (ptr, ...) @printf(ptr @7, ptr @6)
  br label %ifcont

else:                                             ; preds = %argdone
  %printfcall8 = call i32 (ptr, ...) @printf(ptr @9, ptr @8)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret i32 0
}

declare i32 @atoi(ptr)

declare i32 @printf(ptr, ...)
