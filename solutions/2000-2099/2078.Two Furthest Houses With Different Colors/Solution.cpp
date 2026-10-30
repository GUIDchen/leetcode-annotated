// 题目：2078. 两栋颜色不同且距离最远的房子（Two Furthest Houses With Different Colors）
// 思路：首尾颜色不同则答案就是 n-1；否则分别从左侧、右侧找第一个与 colors[0] 不同的位置，取两种走法能形成的最大距离。
// 时间复杂度：O(n)，两个指针合起来最多扫一遍数组；空间复杂度：O(1)，只用了常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDistance(vector<int>& colors) {  // colors：每栋房子的颜色数组，返回值是最远的「异色」两栋的距离
        int n = colors.size();  // 房子总数，后面所有距离都用它来换算
        if (colors[0] != colors[n - 1]) {  // 首尾颜色不同，那么整段首尾就是最远的一对
            return n - 1;  // 0 号与 n-1 号的距离是 n-1，已经是理论最大值
        }  // 结束 if（首尾不同已提前返回）
        int i = 1, j = n - 2;  // i 从左向右、j 从右向左收缩，初值是去掉首尾后的两端
        while (colors[i] == colors[0]) {  // 跳过左端所有与 colors[0] 同色的房子
            ++i;  // 右移，直到停在第一个异色位置 i
        }  // 左指针收缩结束
        while (colors[j] == colors[0]) {  // 跳过右端所有与 colors[0] 同色的房子
            --j;  // 左移，直到停在最后一个异色位置 j
        }  // 右指针收缩结束
        return max(n - i - 1, j);  // 距离 i→n-1 为 n-i-1，距离 0→j 为 j，两者取大即为答案
    }  // 关闭 maxDistance 方法
};  // 关闭 Solution 类
