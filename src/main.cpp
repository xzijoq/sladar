#include <declarations.h>

#include <algorithm>
int testNum = 3*5;
int main()
{
  operators n1 = LCM( testNum );
  cout << "\n AdditiveFactors Are: " << n1.operatorOne << " " << n1.operatorTwo
       << "\n";

  return 0;
}

int Cube(int num) { return num * num * num;}
int Square( int num ) { return num * num; }

operators SubstractiveFactors( int num )
{
  operators factors;
  factors.operatorOne = RandomGen( num, DifficultyRange );
  factors.operatorTwo = factors.operatorOne - num;
  return factors;
}

operators AdditiveFactors( int num )
{
  operators factors;
  factors.operatorOne = RandomGen( 0, num );
  factors.operatorTwo = num - factors.operatorOne;
  return factors;

  /*
  returns num + 0 also maybe change that?
  */
}

operators MultiplicativeFactors( int num )
{
  operators factors = RandomFactors( num );

  return factors;
}
operators DivisiveFactors( int num )
{
  operators factors;
  int maxMultiplier = int( 1000 / num );  // Numerator not larger than 1000
  cout << "\nMaxmu: " << maxMultiplier << "\n";
  factors.operatorTwo = RandomGen( 1, maxMultiplier );
  cout << "\nop1: " << factors.operatorTwo << "\n";
  factors.operatorOne = factors.operatorTwo * num;
  return factors;
}
operators Average( int num )
{
  operators factors;
  int       averageDiviation = RandomGen( 1, num );
  factors.operatorOne = num - averageDiviation;
  factors.operatorTwo = num + averageDiviation;
  return factors;
}
operators Percentage( int num )
{
  operators factors;
  factors.operatorOne = 1;
  factors.operatorTwo = 1;
  operators num1 = RandomFactors( num );

  int witch = RandomGen( 1, 4 );
  switch ( witch )
  {
    case 1:
      factors.operatorOne = 4 * num1.operatorOne;
      factors.operatorTwo = 25 * num1.operatorTwo;
      break;
    case 2:
      factors.operatorOne = 10 * num1.operatorOne;
      factors.operatorTwo = 10 * num1.operatorTwo;
      break;
    case 3:
      factors.operatorOne = 2 * num1.operatorOne;
      factors.operatorTwo = 50 * num1.operatorTwo;
      break;
    case 4:
      factors.operatorOne = 5 * num1.operatorOne;
      factors.operatorTwo = 20 * num1.operatorTwo;
      break;
    default:
      cout << "Buggy percentage";
      break;
  }
  //  int temp;

  return factors;
}

int RandomGen( int numOne, int numTwo )  // inclusive all end, TOO EXPENSIVE
{
  std::random_device rd;  // used to obtain a seed for the random number engine
  std::mt19937       gen( rd() );  // Standard mersenne_twister_engine
  std::uniform_int_distribution<> dis( numOne, numTwo );
  return ( dis( gen ) );
}
std::array<int, MaxFactors + 1> PrimeFactors( int num )
{
  // assert( num < 1000 );
  int                             tracker = 0;
  std::array<int, MaxFactors + 1> PF;  //+1 to hold the number of factors

  for ( int i = 0; i < size( PF ); i++ ) PF[ i ] = 0;

  for ( auto i : Prime0To1000 )
  {
    while ( num % i == 0 )
    {
      PF[ tracker ] = i;
      tracker++;
      assert( tracker <= 10 );
      // MaxFactorsMoreThan 10, number larger than 1024
      num = num / i;
    }
  }

  PF[ MaxFactors ] = tracker;  // last number is number of factors

  return PF;
}
operators RandomFactors( int num )
{
  operators factors;
  factors.operatorOne = 1;
  factors.operatorTwo = 1;
  std::array<int, MaxFactors + 1> PrimeFact = PrimeFactors( num );
  int                             NumOfFactors = PrimeFact[ MaxFactors ];
  if ( NumOfFactors == 1 )
  {  // it's a fucking prime
  }

  int rn = RandomGen( 1, NumOfFactors );  // no zero
  // cout << "\n rn is: " << rn << "\n";
  for ( int i = 0; i < rn; i++ )
  {
    assert( PrimeFact[ i ] != 0 );
    factors.operatorOne = factors.operatorOne * PrimeFact[ i ];
  }
  for ( int i = rn; i < NumOfFactors; i++ )
  {
    factors.operatorTwo = factors.operatorTwo * PrimeFact[ i ];
  }
  // ToDo is prime check skip this operation
  return factors;
}
operators HCF( int num )  // Num should be less than 20
{
  operators factors;
  int       maxRange = 4;  // first 5 primes 20*11 220 limit
  int       rr = RandomGen( 0, maxRange );
  cout << "\nrr: " << rr << "\n";
  factors.operatorOne = num * Prime0To1000[ rr ];
  factors.operatorTwo = num * Prime0To1000[ rr ];
  if ( factors.operatorOne == factors.operatorTwo )  // avoid collision
  {
    factors.operatorTwo = num * Prime0To1000[ ++rr ];  // poor need improve
  }

  return factors;
}



operators LCM( int num )
{
  int       maxNUM=29;
  operators factors;
  factors.operatorOne = -1;
  factors.operatorTwo = -1;
  std::array<int, MaxFactors + 1> tF = PrimeFactors( num );
  std::array<int, MaxFactors + 1> pmF;
  for ( int i = 0; i < size( pmF ); i++ )
  {
    pmF[ i ] = 1;
  }
  cout << "\ntF: ";

  int j{0};
  for ( auto i : tF )
  {
    if ( i > maxNUM )
    {//tooHard
      return factors;
    }
  }
  if ( tF[ MaxFactors ] == 1 )
  {
    return factors;
  }
  for ( int i = 0; i < tF[ MaxFactors ]; i++ )
  {  // int joi=i+1;
    assert( tF[ i ] != 0 );
    pmF[ j ] = pmF[ j ] * tF[ i ];
    while ( tF[ i ] == tF[ i + 1 ] )
    {
      pmF[ j ] = pmF[ j ] * tF[ i ];
      i++;
    }
    j++;
    pmF[ MaxFactors ] = j;
    //
  }
  if ( pmF[ MaxFactors ] == 1 )
  {
    return factors;
  }

  for ( auto i : pmF ) cout << i << " ";
  cout << "asd: " << j;
  int a{1}, b{1};
  //error on 2
  int r1 = RandomGen( 1, pmF[ MaxFactors ] - 1 );
  // r1 = 1;
  int r2 = RandomGen( r1 + 1, pmF[ MaxFactors ] );
  for ( int i = 0; i < r1; i++ )
  {
    a = a * pmF[ i ];
  }
  for ( int i = r1; i < pmF[ MaxFactors ]; i++ )
  {
    b = b * pmF[ i ];
  }
  
  factors.operatorOne = a;
  factors.operatorTwo = b;
  
  return factors;
}




int FindHCF( int num1, int num2 )
{
  if ( num2 == 0 ) return num1;
  return FindHCF( num2, num1 % num2 );
}
int FindLCM( int num1, int num2 )
{
  int LCM = 0;
  if ( num1 > num2 )
    LCM = num1;
  else
    LCM = num2;
  while ( true )
  {
    if ( LCM % num1 == 0 && LCM % num2 == 0 )
    {
      return LCM;
      break;
    }
    LCM++;
  }
}
/*DEBUG

operators n1= AdditiveFactors( testNum );
cout <<"\n AdditiveFactors Are: "<< n1.operatorOne << " " <<
n1.operatorTwo<<"\n";

operators n1 = SubstractiveFactors( testNum );
cout << "\n AdditiveFactors Are: " << n1.operatorOne << " " << n1.operatorTwo
<< "\n";


std::array<int, MaxFactors + 1> testq = PrimeFactors( testNum );
for ( auto i : testq )
{
cout << i << " ";
}

operators factors;
return factors;
*/
