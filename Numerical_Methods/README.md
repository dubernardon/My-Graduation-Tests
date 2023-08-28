# Status registers - IEEE 754

<div align="center"> 
The main algorithm output is a flag of the processor status register. Arithmetic operations (+, -, *, /) are performed by user input in the format: value1 operator value2. When a correct input is provided, the calculation is performed, showing the values ​​in IEEE-754 format and which status registers were activated.
</div>

<div > 
 
**\-  Examples:** 

</div>


<div > 
 
**\  Invalid operation:** 
![invalid_op](https://github.com/dubernardon/My-Graduation-Tests/assets/102065589/25c58d38-bf32-4368-9be8-099b86b70050)

</div>

<div > 
 
**\  Overflow operation:** 
![overflow_op](https://github.com/dubernardon/My-Graduation-Tests/assets/102065589/b063c1a5-786f-40fa-b79c-f111bc2855ea)

</div>

<div > 
 
**\  Underflow operation:** 
![underflow_op](https://github.com/dubernardon/My-Graduation-Tests/assets/102065589/635accbb-fb42-4df4-b3eb-322c434c4372)


</div>

<div > 
 
**\  Division by zero operation:** 

![div0_op](https://github.com/dubernardon/My-Graduation-Tests/assets/102065589/6b96bf9f-589c-432e-ada7-229b8a354adc)

</div>

<div > 
 
**\  Inexact operation:** 
![inexact_op](https://github.com/dubernardon/My-Graduation-Tests/assets/102065589/b6fdfe1a-6ca5-4a43-b084-eb4bc39fa099) 

</div>

<div align="center"> 
  
 **\-  To compile this .c you need to use -lm for fenv.h library works properly, like: gcc status_register -o status_register -lm** 
</div>


<div align="center"> 
 🙋‍♂️ Thanks for visiting my repository!
</div>
