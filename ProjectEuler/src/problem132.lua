local exp = math.pow(10, 9)
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
   return ret
end

-- modular exponentation(clrs-p539)
function dividable(n)
   -- 10^exp % n
   function bl(x)
      return 31
   end
   local c = 0
   local d = 1
   for i = bl(exp) - 1, 0, -1
   do
      c = 2 * c
      d = (d * d) % n
      if bit32.btest(exp, bit32.lshift(1, i))
      then
         c = c + 1
         d = (d * 10) % n
      end
   end
   return d == 1
end

local start = os.time()
local sum = 0
local c = 0
for _, v in pairs(primes(200000))
do
   if dividable(v)
   then
      c = c + 1
      --print("found " .. v .. "(" .. c .. ")")
      sum = sum + v
      if c == 40
      then
         break
      end
   end
end

print(c .. " primes found, sum is " .. sum)
print(
os.time() - start.. " seconds elapsed.."
)


























































































