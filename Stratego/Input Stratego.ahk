#SingleInstance Force
^!1::
for i,x in Object(6,6,7,7,8,8,9,9)
{
	for j,y in Object(0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9)
	{
		Send %x%`,%y%{Enter}
	}
}
return
^!2::
for i,x in Object(0,0,1,1,2,2,3,3)
{
	for j,y in Object(0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9)
	{
		Send %x%`,%y%{Enter}
	}
}
return