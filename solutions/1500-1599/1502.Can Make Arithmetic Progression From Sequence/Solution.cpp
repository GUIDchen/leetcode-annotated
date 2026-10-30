// 题目：1502. 判断能否形成等差数列（Can Make Arithmetic Progression From Sequence）
// 思路：先升序排序，公差取前两个元素之差，再逐个检查后续相邻差是否都等于该公差。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(log n)，sort 的递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    bool canMakeArithmeticProgression(vector<int>& arr) {  // arr：输入数组；返回能否把数组重排成等差数列（排序后再判断即可）
        sort(arr.begin(), arr.end());  // 升序排序：等差序列排序后相邻差必然处处相等
        int d = arr[1] - arr[0];  // 公差取排序后前两个元素之差（题目保证长度 >= 2）
        for (int i = 2; i < arr.size(); i++) {  // 从第三个元素起逐个校验
            if (arr[i] - arr[i - 1] != d) {  // 当前相邻差与公差不同
                return false;  // 不满足等差，返回 false
            }
        }
        return true;  // 全部相邻差都等于公差，返回 true
    }
};