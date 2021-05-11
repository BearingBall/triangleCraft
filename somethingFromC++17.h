#ifndef SOMETHINGFROMC17_H
#define SOMETHINGFROMC17_H



template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi)
{
    return v < lo ? lo : hi < v ? hi : v;
}



#endif // SOMETHINGFROMC17_H
