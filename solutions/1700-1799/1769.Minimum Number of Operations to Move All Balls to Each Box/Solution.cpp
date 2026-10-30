// 题目：1769. 移动所有球到每个盒子所需的最小操作数（Minimum Number of Operations to Move All Balls to Each Box）
// 思路：前后缀递推。left[i] 记录 i 左侧所有球移到 i 的代价，right[i] 记录右侧的代价，两者相加就是该盒子所需的最小操作数；扫描时用已出现的球数 cnt 做增量累加。
// 时间复杂度：O(n)，共三次线性扫描；空间复杂度：O(n)，left、right、ans 三个数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minOperations(string boxes) {  // boxes 是只含 '0'/'1' 的字符串，返回每个盒子所需的最小操作数
        int n = boxes.size();  // 盒子的个数
        int left[n];  // left[i] 表示把 i 左侧的所有球移到 i 所需的操作数（变长数组，clang/gcc 支持）
        int right[n];  // right[i] 表示把 i 右侧的所有球移到 i 所需的操作数
        memset(left, 0, sizeof left);  // left 数组清零，保证初值为 0
        memset(right, 0, sizeof right);  // right 数组清零，保证初值为 0
        for (int i = 1, cnt = 0; i < n; ++i) {  // 从左往右扫描，cnt 表示 i 左侧已经出现的球数
            cnt += boxes[i - 1] == '1';  // boxes[...] == '1' 的真值就是 1，直接累加到 cnt
            left[i] = left[i - 1] + cnt;  // 递推：左侧代价 = 左一格的代价 + 左侧球数（每个球都要多走一步）
        }
        for (int i = n - 2, cnt = 0; ~i; --i) {  // 从右往左扫描；~i 等价于 i >= 0，为真就继续
            cnt += boxes[i + 1] == '1';  // 右侧球数累加
            right[i] = right[i + 1] + cnt;  // 递推：右侧代价 = 右一格的代价 + 右侧球数
        }
        vector<int> ans(n);  // 答案数组，共 n 个元素
        for (int i = 0; i < n; ++i) ans[i] = left[i] + right[i];  // 左右两侧代价相加即该盒子的总操作数
        return ans;  // 返回答案数组
    }  // 方法结束
};  // 类定义结束