function isprime(n)
   if(n % 2 == 0)
   then
      return false
   end
   local s = math.sqrt(n)
   for i = 3, s, 2
   do
      if(n % i == 0)
      then
         return false
      end
   end
   return n % s ~= 0
end

function cube(n)
   return n * n * n
end

--[[
a^3 + pa^2 = b^3
a^3(1 + p/a) = b^3
cube((p + a) / a) = b^3
cube(p + a) / cube(a) = b
both p + a and a are perfect cube.
p = (p + a) - a = x^3 - y^3 
   = (x - y)(x^2 + xy + y^2)
p is a prime, x - y must be 1.
p is the difference between two continuous perfect cube.
]]--

local c = 0
for i = 2, 1000000
do
   local p = cube(i) - cube(i - 1)
   if p >= 1000000
   then
      break
   end
   c = c + (isprime(p) and 1 or 0)
end
print(c)



































