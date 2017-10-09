# Empyrion
A collection of utility classes and functions used in SFEngine, developed outside the engine for modularity 

### Contents  
---  
#### Comparison Functors  
* ```IsBetween``` - meant to be used to ease bounds checking  
  - Another version in the works, to be used alongside functions that require a unary predicate, such as ```std::remove_if```, etc.  
  
#### Transform  
* ```TransformIf(Begin, End, Predicate, Transform)```  
* ```TransformIfNot(Begin, End, Predicate, Transform)```  
* ```ForEachIf(Begin, End, Predicate, UnaryFunc)```  

#### Generators  
* ```GenIota(Count, InitialVal, Increment)``` - generate a sequence of values beginning with InitialVal and incremented by ```Increment``` (this will resize the container passed)  

#### Iterators  
* ```RangeIterator``` - templated for integral types.  Used to iterate over a range of values one-by-one  
eg  
```cpp  
for (auto & i : iRange(0, 10)) {  
  std::cout << i << " ";
}  
```  
will print  
```cpp  
0 1 2 3 4 5 6 7 8 9 10
```  

* ```ReverseRangeIterator``` - similar to above, but iterates from high to low  
eg  
```cpp  
for (auto & i : iRange_r(0, 10)) {
  std::cout << i << ", ";
}  
```  
will print  
```cpp  
10 9 8 7 6 5 4 3 2 1 0  
```  

* ```FloatRangeIterator``` - Takes a low and high like above, but also ```increment``` which will be the delta between iterator values.  Not to be used for cases in which large rounding error could occur or in which the addition of ```increment``` results in no change between values.  In the former case, it will get stuck; in the former, iterator vaues will become incresingly inaccurate.  

#### Random number/sequence generators  
*  Uniform - generate uniform random numbers between two given values. Uses [std::uniform_real_distribution](http://www.cplusplus.com/reference/random/uniform_real_distribution/) and [std::default_random_engine](http://www.cplusplus.com/reference/random/default_random_engine/)  
* Duration - generate random durations between two given durations.  Uses Uniform and Time's Duration class  

#### Spacial random generators  
* Circle - randomly generate points along the circumference of a circle  
* Direction - randomly generate vectors pointing in a direction, randomly deviated by -Deviation to +Deviation  
* CircularArea - randomly generate points inside the area defined by the Center of a circle and its Radius  
* Line - randomly generate points along a line defined by 2 points  
* Radial - randomly generate vectors with a random angle between two given angles and a random magnitude between two given values  

