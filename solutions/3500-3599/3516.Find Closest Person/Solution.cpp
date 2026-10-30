// 题目：3516. 找到最近的人（Find Closest Person）
// 思路：分别算出两人到位置 z 的距离，距离小的人最近；相等则返回 0。
// 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findClosest(int x, int y, int z) {  // x、y：两人的位置；z：参照位置；返回最近的人的编号
        int a = abs(x - z);  // a：第一个人到 z 的距离
        int b = abs(y - z);  // b：第二个人到 z 的距离
        return a == b ? 0 : (a < b ? 1 : 2);  // 距离相等返回 0；否则 a 更近返回 1，b 更近返回 2
    }  // 方法结束
};  // 类结束