// 题目：4. 寻找两个正序数组的中位数（Median of Two Sorted Arrays）
// 思路：把中位数转化为「第 k 小」，每轮比较两数组第 k/2 个元素，淘汰较小的一半并让 k 减半，递归逼近答案。
// 时间复杂度：O(log(m + n))，k 每层减半；空间复杂度：O(log(m + n))，递归调用的栈深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {  // 两个升序数组，返回合并后的中位数
        int m = nums1.size(), n = nums2.size();  // 先取出长度，供下面 lambda 按引用捕获
        function<int(int, int, int)> f = [&](int i, int j, int k) {  // 递归函数 f(i, j, k)：在 nums1[i..]、nums2[j..] 中找第 k 小；用 function 才能递归调用自身
            if (i >= m) {  // nums1 已取空
                return nums2[j + k - 1];  // 答案落在 nums2
            }
            if (j >= n) {  // nums2 已取空
                return nums1[i + k - 1];  // 答案落在 nums1
            }
            if (k == 1) {  // 只剩一个名额
                return min(nums1[i], nums2[j]);  // 取两个候选头部的较小者
            }
            int p = k / 2;  // 每轮可淘汰的步长
            int x = i + p - 1 < m ? nums1[i + p - 1] : 1 << 30;  // nums1 的第 p 个候选；越界时用 2^30 当哨兵
            int y = j + p - 1 < n ? nums2[j + p - 1] : 1 << 30;  // nums2 的第 p 个候选，越界同样用哨兵
            return x < y ? f(i + p, j, k - p) : f(i, j + p, k - p);  // 较小的一段被整体排除，k 减去 p 后继续递归
        };
        int a = f(0, 0, (m + n + 1) / 2);  // 左中位数
        int b = f(0, 0, (m + n + 2) / 2);  // 右中位数；总数为奇数时与 a 相同
        return (a + b) / 2.0;  // 取平均，得到浮点数结果
    }
};