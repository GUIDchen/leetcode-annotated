# 题目：2525. 根据规则将箱子分类（Categorize Box According to Criteria）
# 思路：分别判断 bulky（任一边 >= 10000 或体积 >= 1e9）与 heavy（质量 >= 100），用两个位拼成类别下标。
# 时间复杂度：O(1)，只做常数次比较与乘法；空间复杂度：O(1)，仅用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def categorizeBox(self, length: int, width: int, height: int, mass: int) -> str:  # length/width/height 是三边，mass 是质量，返回箱子所属类别
        v = length * width * height  # 体积（Python 整数无溢出问题，直接相乘）
        bulky = int(any(x >= 10000 for x in (length, width, height)) or v >= 10**9)  # bulky 判定：任一边 >= 1e4 或体积 >= 1e9，任一成立即为 1
        heavy = int(mass >= 100)  # heavy 判定：质量 >= 100 时为 1
        i = heavy << 1 | bulky  # 把 heavy 放到高位、bulky 放到低位，拼出 0/1/2/3 作为下标
        d = ['Neither', 'Bulky', 'Heavy', 'Both']  # 四个类别字符串，下标正好是 0 到 3
        return d[i]  # 按拼出的下标返回类别名
