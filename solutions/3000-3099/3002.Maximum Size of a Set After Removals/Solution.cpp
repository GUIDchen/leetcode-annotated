// 题目：3002. 移除后集合的最多元素数（Maximum Size of a Set After Removals）
// 思路：两数组各自去重后分成「只属 nums1」「只属 nums2」「两边共有」三块；每边最多只能贡献 n/2 个，独有部分先截到 n/2，再加上共有部分与总数 n 取小。
// 时间复杂度：O(n)，建哈希表与两次遍历都是线性；空间复杂度：O(n)，两个去重集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {  // nums1 / nums2：长度同为 n 的两个数组；返回各删掉 n/2 个元素后，两集合元素种类数的最大值
        unordered_set<int> s1(nums1.begin(), nums1.end());  // nums1 去重，得到它包含的全部不同元素
        unordered_set<int> s2(nums2.begin(), nums2.end());  // nums2 去重
        int n = nums1.size();  // 两数组等长，记录 n 以确定每边最多能保留 n / 2 个元素
        int a = 0, b = 0, c = 0;  // a：只出现在 nums1 的元素个数；b：只出现在 nums2 的个数；c：两边都有的个数
        for (int x : s1) {  // 遍历 nums1 去重后的元素，统计它独有的部分
            if (!s2.count(x)) {  // 该元素不在 nums2 中，说明是 nums1 独有
                ++a;  // 独有计数加一
            }
        }
        for (int x : s2) {  // 遍历 nums2 去重后的元素，区分独有与共有
            if (!s1.count(x)) {  // 该元素不在 nums1 中，说明是 nums2 独有
                ++b;  // nums2 独有计数加一
            } else {  // 否则这个元素两个数组都有
                ++c;  // 共有元素计数加一
            }
        }
        a = min(a, n / 2);  // nums1 最多只能从自身贡献 n / 2 个元素，多出来的必须删掉
        b = min(b, n / 2);  // nums2 同理，最多贡献 n / 2 个
        return min(a + b + c, n);  // 独有部分各取上限后相加，再加上共有部分，但集合总大小不会超过 n
    }
};