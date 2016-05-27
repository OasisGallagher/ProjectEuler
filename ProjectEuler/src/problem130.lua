function replen(n)
   local r = 1
   local rem = 1
   while rem ~= 0
   do
      rem = (rem * 10 + 1) % n
      r = r + 1
   end
   return r
end

function numok(n)
   if(n % 2 == 0 or n % 5 == 0)
   then -- not coprime to 10.
      return false
   end
   local s = math.sqrt(n)
   for i = 3, s, 2
   do
      if(n % i == 0)
      then -- not prime
         return true
      end
   end
   return n % s == 0
end

local count = 0
local n = 91
local sum = 0
print("started ...")
while count ~= 25
do
   --print("checking " .. n)
   if((n - 1) % replen(n) == 0)
   then
      count = count + 1
      --print(count .. ": " .. n)
      sum = sum + n
   end
   repeat
      n = n + 1
   until(numok(n))
end

print("result: " .. sum)












































