// 题目：2683. 相邻值的按位异或（Neighboring Bitwise XOR）
// 思路：把原数组相邻异或一圈后每一项都会出现两次，整体异或必为 0；因此 array 存在当且仅当 derived 全体异或结果为 0。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool doesValidArrayExist(vector<int>& derived) {  // derived：相邻异或得到的结果数组
        int s = 0;  // 异或的累加器，初值 0 是异或的单位元
        for (int x : derived) {  // 遍历 derived 的每一个元素
            s ^= x;  // 把当前元素异或进累加器
        }  // 遍历结束
        return s == 0;  // 全部异或为 0 说明能还原出合法原数组
    }  // 方法结束
};  // 类定义结束