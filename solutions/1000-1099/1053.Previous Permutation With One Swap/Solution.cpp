// 题目：1053. 交换一次的先前排列（Previous Permutation With One Swap）
// 思路：从右往左找第一个 arr[i-1] > arr[i] 的断点，再在断点右侧从右往左找小于断点值的最大元素交换，即可得到最大的先前排列。
// 时间复杂度：O(n)，最多扫描两遍；空间复杂度：O(1)，只在原数组上交换。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> prevPermOpt1(vector<int>& arr) {  // arr：当前排列；返回交换一次后能得到的最大「先前排列」
        int n = arr.size();  // 排列长度
        for (int i = n - 1; i > 0; --i) {  // 从右往左找第一个可以变小的位置：arr[i-1] > arr[i]
            if (arr[i - 1] > arr[i]) {  // 找到断点，说明把 i-1 处的值换小就能得到更小的排列
                for (int j = n - 1; j > i - 1; --j) {  // 在断点右侧从右往左找合适的元素来交换
                    if (arr[j] < arr[i - 1] && arr[j] != arr[j - 1]) {  // 取小于断点值中最大的那个；跳过与前一位相等的值以免换错位置
                        swap(arr[i - 1], arr[j]);  // 交换一次，右侧保持原升序即得最大的先前排列
                        return arr;  // 题目只允许交换一次，交换后立即返回
                    }  // 内层 if 结束
                }  // 候选元素枚举结束
            }  // 断点判断结束
        }  // 外层扫描结束
        return arr;  // 不存在先前排列（本身已非递减），原样返回
    }  // 方法结束
};  // 题解类结束