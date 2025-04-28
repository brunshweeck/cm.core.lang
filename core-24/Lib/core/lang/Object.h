//
// Created by brunshweeck on 01/04/25.
//

#ifndef CORE_LANG_OBJECT_H
#define CORE_LANG_OBJECT_H

#include "spi/Literals.h"

namespace core
{
    /// The class @c Object is base of all class hierarchy.
    class Object
    {
    protected:
        /// The constructor, only accessible with inherited class
        CORE_FAST Object() = default;

    public:
        virtual ~Object() = default;

        /**
         *  Test whether some other object is "equal to" this one.
         *  The @c equals method implements an equivalence relation on non-null object references:
         *  - It's @a reflexive: For any reference value @c X, @c X.equals(X) should return @c true;
         *  - It's @a symmetric: For any reference values @c X and @c Y, @c X.equals(Y) should return @c true if and only if @c Y.equals(X);
         *  - It's @a transitive: For any reference values @c X, @c Y and @c Z, if @c X.equals(Y) return @c true, and @c Y.equals(Z) return @c true, then @c X.equals(Z) should be return @c true;
         *  - It's @a consistent : For any reference value @c X and @c Y, multiple invocation of @c X.equals(Y) consistently return @c true, or consistently return @c false provided no information used in @c equals  comparisons on the objects is modified.
         * @param other The object to be compared with this object
         * @return The value @c true if this instance equals to given object.
         */
        virtual gboolean equals(Object const& other) const;

        /**
         *  Returns a hash code value for the object. This method is supported for the benefit of hash tables such as those provided by  @c core::util::HashTable
         *  The general contract of @c hash is:
         *  - Whenever it is invoked on the same object more than once during an execution of an application, the @c hash method must consistently return the same integer, provided no information used in @c equals comparisons on the object is modified. This integer need not remain consistent from one execution of an  application to another execution of the same application.
         *  -  If two objects are equal according to the @c equals  method, then calling the @c hash  method on each of the two objects must produce the  same integer result.
         *  -  It is @a not required that if two objects are unequal according to the @c equals method, then calling the @c hash method on each of the two objects must produce  distinct integer results.  However, the programmer  should be aware that producing distinct integer results for unequal objects may improve the performance of hash tables.
         * @return  The hash code value for this object
         * @note  As far as is reasonably practical, the @c hash method defined by class @c Object returns distinct integers for distinct objects.
         */
        virtual gint hash() const;

        /**
         *  Returns a string representation of the object.
         *  In general, the @c toString method returns a string that @c "textually represents" this object. The result should be a concise but informative representation that is easy for a person to read.
         * @return A string representation of the object.
         * @note It is recommended that all subclasses override this method.
         * todo: uncomment and implement method toString
         */
        virtual String toString() const;

        /**
         *  Create and return the shadow and dynamic copy of this object.
         *  The precise meaning @em copy may depend on the class of object.
         *  The General intent is that, for any object @c X, the expression:
         *  - address of @c X  not equals to address of @c X.clone() and @c X.clone() must be an instance of same type with @c X, but these are not absolute requirement;
         *  - While it is typically the case that: @c X.equals(X.clone()) will be @c true, this is not absolute.
         *  @return The shadow copy of this object.
         *  @note By convention, the returned object should be independent for this object (which is being cloned)
         *  @throws CloneNotSupportedException If the object's class does not support the @c clone operation. Subclasses that override the @c clone method can also throw this exception to indicate that an instance cannot be cloned.
         *  todo: uncomment and implement method clone
         */
        virtual Object& clone() const = 0;
    };
} // core

#endif //CORE_LANG_OBJECT_H
