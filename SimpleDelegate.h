#pragma once

/** a very simple version of http://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible
down to under 100 lines vs 2000 lines using some tricky macro business and removing some of the multi compiler support
as well as removing a few of the plethora of ways to bind 
hopefully this is still able to cross compile on a bunch of different machines usages....
SimpDelegate2<int, char*> adelegate; //creates the delegate
adelegate.bind(&aclass, &class::classmember);//binds the delegate to the class/MFP
adelegate(5,"wow cool");//calls the MFP using the class
*/
namespace SimpleDelegate
{
	namespace PrivateNames
	{// some simple support routines are located here
		class UnknownClass
		{
		};

		// credit to Don for creating this simple cast changes the pointer from related classes
		template <class OutputClass, class InputClass>
		inline OutputClass implicit_cast(InputClass input){
			return input;
		}
	}

// the entire mechanism is enclosed in a macro which allows for one code base to create all the delegates for the different parameter lengths
#define SimpDelegateMaker(TEMPLATETYPES, CLASSNAME, PARAMS,PARAMSCALLED)\
template<TEMPLATETYPES typename rettype=void> \
class CLASSNAME\
{\
private:\
	typedef rettype (PrivateNames::UnknownClass::* UnknownClassFuncPtr)(PARAMS);\
	UnknownClassFuncPtr member;\
	PrivateNames::UnknownClass *callee;\
/*internally used function to copy the MFP data from one to the other*/\
	void CommonBind(void *object, void *funcptr, int ptrsize)\
	{\
		callee = (PrivateNames::UnknownClass*)object;\
		if(sizeof(member)==ptrsize)\
		{\
			memcpy(&member,funcptr,sizeof(funcptr));\
\
		}\
		else\
		{\
			fprintf(stderr,"MFP sizes do not match\n");\
		}\
	}\
\
public:\
\
	CLASSNAME()\
	{\
		member = NULL;\
		callee = NULL;\
	}\
\
	inline bool operator ! () const	{return !member; }\
			/*bind use for normal MFP's*/\
	template<class A,class B> \
	void bind(A *object, rettype (B::*funcptr)(PARAMS))\
	{CommonBind(PrivateNames::implicit_cast<B*>(object), &funcptr,sizeof(funcptr));}\
/*bind use for const MFP's*/\
	template<class A,class B> \
	void bind(A *object, rettype (B::*funcptr)(PARAMS) const)\
	{CommonBind(PrivateNames::implicit_cast<B*>(object), &funcptr,sizeof(funcptr));}\
/*operator overloading to be able to call the class using function convensions*/\
	rettype operator()(PARAMS) const\
	{\
		return (callee->*member)(PARAMSCALLED);\
	}\
};


/*all the macro use cases to expand from 0 to 3 argument versions of the template class
this could be expanded to any number of arguments as necessary*/
SimpDelegateMaker(,SimpDelegate0,,)

#define SimpDel1Temp typename T1,
SimpDelegateMaker(SimpDel1Temp,SimpDelegate1,T1 p1,p1)

#define SimpDel2Temp typename T1, typename T2,
#define SimpDel2Params T1 p1, T2 p2
#define SimpDel2Call p1, p2
SimpDelegateMaker(SimpDel2Temp,SimpDelegate2,SimpDel2Params,SimpDel2Call)


#define SimpDel3Temp typename T1, typename T2, typename T3,
#define SimpDel3Params T1 p1, T2 p2, T3 p3
#define SimpDel3Call p1, p2, p3
SimpDelegateMaker(SimpDel3Temp,SimpDelegate3,SimpDel3Params,SimpDel3Call)

// add as many as you need here to increase the parameter count
// or use the macro to change the name of the delegate class

};
