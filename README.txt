DEVELOPER NOTES:

<--------------------------------------------------->
<--------------Control Signals Design -------------->
<--------------------------------------------------->


<--------------------------------------------------->
BIT 0
<--------------------------------------------------->
RegWrite

--Is anything being written to the registers?


<--------------------------------------------------->
BIT 1
<--------------------------------------------------->
R/I Type

--Is it an R (0) or I (1) type instruction?
--(J-Type gets 0)


<--------------------------------------------------->
BITS 3 - 7
<--------------------------------------------------->
ALUOP

--Defines what operation the ALU will run.
--Full list in Control Signals.xlsx


<--------------------------------------------------->
BIT 8
<--------------------------------------------------->
MemWrite

--Is anything being written to Data Memory?


<--------------------------------------------------->
BIT 9
<--------------------------------------------------->
MemRead

--Is anything being read from Data Memory?


<--------------------------------------------------->
BIT 10
<--------------------------------------------------->
MemToReg

--Is any value being passed from Data Memory to
--the register file?


<--------------------------------------------------->
BIT 11
<--------------------------------------------------->
J-Type

--Is this instruction a J-Type instruction?


<--------------------------------------------------->
BIT 12
<--------------------------------------------------->
Branch

--Is this instruction a branch instruction?


<--------------------------------------------------->
BIT 13
<--------------------------------------------------->
LogComp

--Is this instruction a logical comparison?
--NOTE: This value is 0 for branches that use
--logical comparisons within them.