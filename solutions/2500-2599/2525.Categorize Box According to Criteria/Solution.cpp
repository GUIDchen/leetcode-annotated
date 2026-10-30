// 题目：2525. 根据规则将箱子分类（Categorize Box According to Criteria）
// 思路：分别判断 bulky（任一边 >= 10000 或体积 >= 1e9）与 heavy（质量 >= 100），用两个位拼成类别下标。
// 时间复杂度：O(1)，只做常数次比较与乘法；空间复杂度：O(1)，仅用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string categorizeBox(int length, int width, int height, int mass) {  // length/width/height 是三边，mass 是质量，返回箱子所属类别
        long v = (long) length * width * height;  // 体积可能到 1e4^3=1e12，必须用 long 才不会溢出 int
        int bulky = length >= 10000 || width >= 10000 || height >= 10000 || v >= 1000000000 ? 1 : 0;  // bulky 判定：任一边 >= 1e4，或体积 >= 1e9，满足为 1 否则为 0
        int heavy = mass >= 100 ? 1 : 0;  // heavy 判定：质量 >= 100 时为 1，否则为 0
        string d[4] = {"Neither", "Bulky", "Heavy", "Both"};  // 四个类别字符串，下标正好由「heavy 位 + bulky 位」组成 0..3
        int i = heavy << 1 | bulky;  // 把 heavy 放到高位、bulky 放到低位，拼出 0/1/2/3 作为下标
        return d[i];  // 按下标取出并返回类别名
    }  // 方法结束
};  // 类定义结束