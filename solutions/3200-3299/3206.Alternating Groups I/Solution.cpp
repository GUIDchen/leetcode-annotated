// 题目：3206. 交替组 I（Alternating Groups I）
// 思路：把环形数组首尾相接扫两圈，用 cnt 维护当前「相邻两数交替」的连续段长度；进入第二圈后，cnt ≥ 3 就说明出现了一个长度为 3 的交替组。
// 时间复杂度：O(n)，只扫 2n 个位置；空间复杂度：O(1)，仅用常数个变量。
class Solution {  // LeetCode 题解类，固定入口名
public:  // 解法方法对外可见
    int numberOfAlternatingGroups(vector<int>& colors) {  // 统计长度为 3 的交替组个数；colors 为环形颜色数组
        int k = 3;  // 本题交替组的固定长度是 3
        int n = colors.size();  // 环形数组的长度
        int ans = 0, cnt = 0;  // ans 计答案，cnt 记录当前连续交替段的长度
        for (int i = 0; i < n << 1; ++i) {  // 扫两圈（2n）以跨越首尾边界，i 取模映射回原数组
            if (i && colors[i % n] == colors[(i - 1) % n]) {  // 若当前颜色与前一个颜色相同，说明交替在这里断开
                cnt = 1;  // 重新开始一段，长度记为 1（它自己）
            } else {  // 否则颜色交替
                ++cnt;  // 交替段长度加一
            }  // 分支结束
            ans += i >= n && cnt >= k ? 1 : 0;  // 只在第二圈统计，避免同一组被重复计数；长度达到 3 就是一个合法交替组
        }  // 两圈遍历结束
        return ans;  // 返回交替组总数
    }  // 方法结束
};  // 题解类结束