// 4062. 成对操作转化数组  Transform Array Using Pair Operations
// 核心思路：每次成对操作都保持数组元素总和不变，因此只需判断两个数组的总和是否相等。
// 复杂度：时间 O(n + m)，空间 O(1)。

class Solution {
public:
    bool canTransform(vector<int>& source, vector<int>& target) {  // 判断 source 能否通过成对操作转成 target
        long long s = 0;  // 用 64 位整数累计总和，避免溢出
        for (int x : source) {  // 遍历源数组的每个元素
            s += x;  // 累加源数组元素
        }
        for (int x : target) {  // 遍历目标数组的每个元素
            s -= x;  // 从累计和中减去目标数组元素
        }
        return s == 0;  // 差值归零说明两数组总和相等，可以互相转化
    }
};
