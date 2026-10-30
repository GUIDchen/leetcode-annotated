// 题目：691. 贴纸拼词（Stickers to Spell Word）
// 思路：状态压缩 BFS。用 n 位掩码表示 target 中已被拼出的位置，从 0 出发，每层尝试贴一张贴纸，按字母计数尽可能多地覆盖未拼出的位置，首次到达全 1 掩码即为最少贴纸数。
// 时间复杂度：O(2ⁿ · m · n)，m 为贴纸数、n 为目标串长度；空间复杂度：O(2ⁿ) 存访问标记与队列。
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {  // stickers 为可用贴纸，target 为要拼出的目标串，返回最少贴纸数
        int n = target.size();  // n 是目标串长度，也是状态掩码的位数
        queue<int> q{{0}};  // BFS 队列，初始状态为掩码 0（什么都没拼出）
        vector<bool> vis(1 << n);  // vis[mask] 标记该掩码是否已经入队，避免重复搜索
        vis[0] = true;  // 起点状态标记为已访问
        for (int ans = 0; q.size(); ++ans) {  // 按层 BFS，ans 记录已使用的贴纸数（每层 +1）
            for (int m = q.size(); m; --m) {  // 逐层取出当前层的全部状态，保证 ans 的层数语义正确
                int cur = q.front();  // 取出队首状态（已拼出的位置掩码）
                q.pop();  // 弹出该状态
                if (cur == (1 << n) - 1) {  // 所有位置都已拼出，说明到达目标状态
                    return ans;  // 返回当前层数即最少贴纸数
                }
                for (auto& s : stickers) {  // 枚举每一张贴纸，尝试用它扩展状态
                    int cnt[26]{};  // cnt 统计这张贴纸里每个字母的个数（值初始化全 0）
                    int nxt = cur;  // nxt 是从 cur 出发贴上该贴纸后得到的新掩码
                    for (char& c : s) {  // 统计贴纸中每个字母的出现次数
                        ++cnt[c - 'a'];  // 字母 c 的出现次数加一，下标为字符与 'a' 的差值
                    }
                    for (int i = 0; i < n; ++i) {  // 扫描目标串的每个位置，看贴纸能否补上
                        int j = target[i] - 'a';  // 把当前字符换算成 0~25 的字母下标
                        if ((cur >> i & 1) == 0 && cnt[j] > 0) {  // 该位置尚未拼出，且贴纸里还有这个字母可用
                            nxt |= 1 << i;  // 把第 i 位移入结果掩码，表示该位置已拼出
                            --cnt[j];  // 消耗掉一个该字母，同一张贴纸的字母不能重复使用
                        }
                    }
                    if (!vis[nxt]) {  // 新状态还没被访问过才入队，保证每个状态只扩展一次
                        vis[nxt] = true;  // 标记新状态已访问
                        q.push(nxt);  // 新状态入队，等下一层处理
                    }
                }
            }
        }
        return -1;  // 队列耗尽仍未拼出目标串，说明无法完成，返回 -1
    }
};