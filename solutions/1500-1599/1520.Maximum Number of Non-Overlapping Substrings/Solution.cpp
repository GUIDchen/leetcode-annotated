// 题目：1520. 最多的不重叠子字符串（Maximum Number of Non-Overlapping Substrings）
// 核心思路：先求每个字母的首末位置；把每个字母的区间向右「闭包扩张」成包含其全部出现的最小区间得到候选；再按右端点排序贪心选取互不重叠的区间，个数最多。
// 时间复杂度：O(n + 26·n)，扩张扫描每个字母最多一遍；空间复杂度：O(n)，候选区间与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> maxNumOfSubstrings(string s) {  // s：只含小写字母的字符串，返回数量最多的合法不重叠子串
        int n = s.size();  // n 为字符串长度
        int first[26], last[26];  // first[x]/last[x]：字母 x（0~25）在 s 中第一次、最后一次出现的位置
        memset(first, -1, sizeof(first));  // first 全部置 -1，表示该字母还没出现过；last 会在扫描中被覆盖
        for (int i = 0; i < n; ++i) {  // 从左到右扫描一遍字符串
            int x = s[i] - 'a';  // 把字符映射成 0~25 的下标
            if (first[x] == -1) {  // 如果是首次遇到该字母
                first[x] = i;  // 记录首次出现位置
            }  // if 结束
            last[x] = i;  // 每次都更新最后一次出现位置
        }  // 扫描结束
        vector<pair<int, int>> segs;  // segs 存放所有「合法候选区间」[l, r]
        for (int x = 0; x < 26; ++x) {  // 枚举 26 个字母
            if (first[x] == -1) {  // 该字母在串中没出现过
                continue;  // 跳过它
            }  // if 结束
            int l = first[x], r = last[x];  // 以该字母的首末位置作为初始区间
            int i = l;  // i 用于从左到右扫描这个区间（定义在循环外，便于事后判断 i 与 r 的关系）
            for (; i <= r; ++i) {  // 扩张区间，直到区间内所有字母的出现都被完整包住
                int y = s[i] - 'a';  // 区间内第 i 个字符对应的字母
                if (first[y] < l) {  // 该字母在区间左端 l 的左边还有出现
                    break;  // 合法区间必须更靠左，而左端点已固定，此字母无法成段，直接 break 放弃
                }  // if 结束
                r = max(r, last[y]);  // 否则把右端点扩张到该字母的最后一次出现
            }  // 扫描结束
            if (i > r) {  // i > r 说明区间完整闭合，没有被 break 打断
                segs.emplace_back(l, r);  // 记录这个合法候选区间
            }  // if 结束
        }  // 字母枚举结束
        sort(segs.begin(), segs.end(), [](const auto& a, const auto& b) {  // 按右端点从小到大排序：越早结束，越能留给后面的区间
            return a.second < b.second;  // 比较两个区间的右端点
        });  // 排序结束
        vector<string> ans;  // 答案列表
        int end = -1;  // end 记录上一个被选区间的右端点，-1 表示还没选过
        for (auto [l, r] : segs) {  // 按右端点顺序遍历候选区间，同时解构出左右端点
            if (l > end) {  // 与已选区间不重叠才选它
                ans.emplace_back(s.substr(l, r - l + 1));  // 截取子串 s[l..r] 放入答案
                end = r;  // 更新已选区间覆盖到的最右位置
            }  // if 结束
        }  // 遍历结束
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束
