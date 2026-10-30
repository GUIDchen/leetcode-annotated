// 题目：3132. 找出与数组相加的整数 II（Find the Integer Added to Array II）
// 思路：排序后枚举 x = nums2[0] - nums1[i]（i 只可能取 0/1/2，因为最多删掉两个元素），用双指针验证能否只丢弃 nums1 中至多 2 个元素就整体平移。
// 时间复杂度：O(n log n)，排序为主要开销；空间复杂度：O(log n)，排序递归栈的额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {  // nums1 是原数组，nums2 是删掉两个元素后整体加 x 的结果
        sort(nums1.begin(), nums1.end());  // 升序排序，使两个数组可以按同样顺序用双指针比较
        sort(nums2.begin(), nums2.end());  // nums2 同样升序排序
        int ans = 1 << 30;  // 答案初始化为无穷大，等待被更小的可行 x 更新
        auto f = [&](int x) {  // 内部 lambda：判断差值 x 是否能在丢弃至多 2 个元素后成立
            int i = 0, j = 0, cnt = 0;  // i 遍历 nums1，j 遍历 nums2，cnt 统计被丢弃的元素个数
            while (i < nums1.size() && j < nums2.size()) {  // 两个数组都还没走到末尾
                if (nums2[j] - nums1[i] != x) {  // 当前元素平移后对不上，说明 nums1[i] 必须被删除
                    ++cnt;  // 丢弃计数加一
                } else {  // 否则能对上，保留这一项
                    ++j;  // nums2 的指针前进，去匹配下一个元素
                }  // if / else 分支结束
                ++i;  // 无论是否匹配，nums1 的指针都要前进
            }  // 双指针扫描结束
            return cnt <= 2;  // 丢弃不超过 2 个元素即说明 x 可行
        };  // lambda 定义结束
        for (int i = 0; i < 3; ++i) {  // nums2[0] 最多只能来自 nums1 的前 3 个元素（前面最多删掉两个）
            int x = nums2[0] - nums1[i];  // 由这一对元素反推出一个候选的 x
            if (f(x)) {  // 检验候选 x 是否可行
                ans = min(ans, x);  // 可行就用更小的 x 更新答案
            }  // 候选可行分支结束
        }  // 三个候选取值枚举结束
        return ans;  // 返回最小的可行 x
    }  // 方法体结束
};  // 类定义结束