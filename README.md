# Empyrion
A collection of utility classes and functions used in SFEngine, developed outside the engine for modularity 

## Contents  
---  
### Comparison Functors  
* ```IsBetween``` - meant to be used to ease bounds checking  
  - Another version in the works, to be used alongside functions that require a unary predicate, such as ```std::remove_if```, etc.  
  
### Transform  
* ```TransformIf(Begin, End, Predicate, Transform)```  
* ```TransformIfNot(Begin, End, Predicate, Transform)```  
* ```ForEachIf(Begin, End, Predicate, UnaryFunc)```  

### Generators  
* ```GenIota(Count, InitialVal, Increment)``` - generate a sequence of values beginning with InitialVal and incremented by ```Increment``` (this will resize the container passed)  

### Iterators  
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

### Random number/sequence generators  
*  Uniform - generate uniform random numbers between two given values. Uses [std::uniform_real_distribution](http://www.cplusplus.com/reference/random/uniform_real_distribution/) and [std::default_random_engine](http://www.cplusplus.com/reference/random/default_random_engine/)  
* Duration - generate random durations between two given durations.  Uses Uniform and Time's Duration class  

### Spacial random generators  
* Circle - randomly generate points along the circumference of a circle  
* Direction - randomly generate vectors pointing in a direction, randomly deviated by -Deviation to +Deviation  
* CircularArea - randomly generate points inside the area defined by the Center of a circle and its Radius  
* Line - randomly generate points along a line defined by 2 points  
* Radial - randomly generate vectors with a random angle between two given angles and a random magnitude between two given values  

### Time classes  
#### Duration  
Abstraction for time management.  Measures internally to the nanosecond level, and stores it internally as milliseconds with ```double``` as the rep.  Can be converted to nanoseconds, milliseconds, and seconds.  

#### StopWatch  
Abstraction for measuring elapsed time.  Internally uses a time point and a duration to measure elapsed time.  Can be paused, resumed, stopped, and restarted.  

#### Timer  
Abstraction for counting down a pre-determined duration.  A callback can be set to automatically be called when it expires.  Its accuracy depends on how often you update its time by calling ```GetTime()```, which internally updates it.  

#### TimeExtent  
Abstraction for representing  time measurability.  This can be used to adjust the perceived and measured rate of time advancement (or reversal).  Time can be slowed by changing the extent's speed, and a negative speed will cause it to reverse. 

#### TimeStep  
Abstraction for measuing fixed time steps and interpolating your rendering if a render happens in-between time steps.

#### TimeExtend  



### Particles  
---  
 
#### Particle  
Has a lifetime, color, velocity, position, and radius.  It is acted on by forces with ParticleAffectors, which will cause a change in velocity over time.  

#### ParticleEmitter  
Emits particles using function objects to select the particles initial position, velocity, etc.  The random spacial generation functors are meant to be used with these to produce interesting emissions.  For example: ```Emitter.SetPosition(distributions::Circle(SVector2f(400.f, 680.f), 100.f));``` will cause a particle emitter to emit particles along the circumference of a circle whose center is at (400, 680) and whose radius is 100 (all in pixel coordinates).  
```Emitter2.SetPosition(distributions::Line(SVector2f(600.f, 100.f), SVector2f(600.f, 800.f)));``` will cause a particle emitter to emit particles randomly along the line segment connecting the two points (600, 100) and (600, 800).  

#### ParticleAffector  
Meant to influcence a particle in some noticable way.  There are ```ForceAffector```, ```AttractionAffector```, ```RepulsionAffector```, and ```ColorAffector```, the last of which will interpoalte a particle's color over its lifetime and can be used to make the particle gently fade out over time.  

#### ParticleSystem  
The main brain.  A max number of particles is set upon construction and a texture passed if desired (highly recommended unless you like square particles).  Internally, dead particles are just rendered invisible so that the container does not have to be reconstructed every frame.
