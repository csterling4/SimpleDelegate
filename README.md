SimpleDelegate
==============

After reading the CodeProject article by Don Clugston http://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible I felt compelled to muck about with the code. The end result is a highly compressed version of his library. I've tested this with visual studio 2003 and GCC 4.8.1, and seems to work using the main supported cases. Most likely this code does not have the same level of compatibility as the original code however I think there is still merit to compressing the problem down to its simplest viable case. I removed support for static member functions and plain C functions as I feel the normal C callback mechanism works well enough for these cases.

-CS
