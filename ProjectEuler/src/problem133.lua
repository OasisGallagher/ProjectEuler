require "bit"
function primes(n)
   local t = {}
   for i = 1, n
   do
      t[i] = (i % 2 ~= 0)
   end
   local ret = {}
   for i = 3, n, 2
   do
      if t[i]
      then
         if i ~= 5 and i ~= 3
         then
            table.insert(ret, i)
         end
         for j = i + i, n, i
         do
            t[j] = false
         end
      end
   end
   print("prime set generated, size: " .. #ret)
   return ret
end

function div(x, n)
   local t = x % n
   while t == 0
   do
      x = x / n
      t = x % n
   end
   return x
end

function fac25(n)
   if n == 1 then return false end
   n = div(n, 2)
   n = div(n, 5)
   return n == 1
end

function steps(n)
   local t = {}
   for i = 2, n
   do
      if fac25(i)
      then
         table.insert(t, i)
      end
   end
   print("steps generated, size " .. #t)
   return t
end

function expmod(x, e, y)
   function testbit(n, p)
      return bit.band(n, bit.lshift(1, p)) ~= 0
   end

   function el(n)
      for i = 31, 0, -1
      do
         if testbit(n, i)
         then
            return i
         end
      end
      return 31
   end

   local d = 1
   for i = el(e), 0, -1
   do
      d = (d * d) % y
      if testbit(e, i)
      then
         d = (d * x) % y
      end
   end
   return d
end

local start = os.time()
local Max = 100000
local st = steps(Max - 1)

function ok(p)
   for _, v in pairs(st)
   do
      if (v >= p)
      then
         return true
      end
      if expmod(10, v, p) == 1
      then
         return false
      end
   end
   return true
end

local c = 2 + 3 + 5
for _, p in pairs(primes(Max))
do
   if(ok(p))
   then
      c = c + p
   end
end
print("result is " .. c)
print(os.time() - start.. " seconds elapsed..")
