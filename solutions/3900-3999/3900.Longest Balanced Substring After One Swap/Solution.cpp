// 3900. 一次交换后的最长平衡子串 / Longest Balanced Substring After One Swap
// 核心思路：把 1 记 +1、0 记 -1 求前缀和，同前缀和的距离给出不交换时的答案；交换只能让区间差值改变 0 或 ±2，故再查相差 2 的前缀和位置，判断区间内是否还有可交换的字符。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有接口
    int longestBalanced(string s) {  // s 为 0/1 串，返回至多交换一次后能得到的最长平衡子串长度
        int cnt0 = count(s.begin(), s.end(), '0');  // 统计全串 0 的个数
        int cnt1 = s.size() - cnt0;  // 全串 1 的个数
        unordered_map<int, vector<int>> pos;  // 记录每个前缀和出现过的所有下标
        pos[0] = {-1};  // 空前缀和为 0，位置记为 -1
        int ans = 0, pre = 0;  // ans 为答案，pre 为当前前缀和（1 记 +1，0 记 -1）
        for (int i = 0; i < s.size(); ++i) {  // 从左到右枚举右端点
            pre += s[i] == '1' ? 1 : -1;  // 更新前缀和
            pos[pre].push_back(i);  // 记录该前缀和出现的位置

            ans = max(ans, i - pos[pre][0]);  // 不交换时，同一前缀和的最远左端点即可构成平衡子串
            if (pos.contains(pre - 2)) {  // 相差 2 说明区间内 1 比 0 多 2，需要把一个 0 换进来
                auto& p = pos[pre - 2];  // 取出该前缀和的全部出现位置
                if ((i - p[0] - 2) / 2 < cnt0) {  // 区间内还有多余的 0 可交换，整段可以保留
                    ans = max(ans, i - p[0]);  // 以最远左端点更新答案
                } else if (p.size() > 1) {  // 否则需要退到次远左端点，把缺的 1 挤出去
                    ans = max(ans, i - p[1]);  // 用次远位置更新答案
                }  // 该前缀和处理结束
            }  // 左侧分支结束

            if (pos.contains(pre + 2)) {  // 相差 2 说明区间内 0 比 1 多 2，需要把一个 1 换进来
                auto& p = pos[pre + 2];  // 取出该前缀和的全部出现位置
                if ((i - p[0] - 2) / 2 < cnt1) {  // 区间内还有多余的 1 可交换，整段可以保留
                    ans = max(ans, i - p[0]);  // 以最远左端点更新答案
                } else if (p.size() > 1) {  // 否则需要退到次远左端点，把缺的 0 挤出去
                    ans = max(ans, i - p[1]);  // 用次远位置更新答案
                }  // 该前缀和处理结束
            }  // 右侧分支结束
        }  // 枚举结束
        return ans;  // 返回最长平衡子串长度
    }  // longestBalanced 结束
};  // 类定义结束