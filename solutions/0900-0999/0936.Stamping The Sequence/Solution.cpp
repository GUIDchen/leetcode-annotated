// 题目：936. 戳印序列（Stamping The Sequence）
// 思路：反向拓扑排序（BFS）。把每个盖章起点当作节点，入度是还需要被覆盖的错位数；入度为 0 表示此刻就能盖，盖章后再解锁依赖这些位置的节点。
// 时间复杂度：O(n*m)，每个盖章位置与每个字符位置各处理常数次；空间复杂度：O(n*m)，邻接表的总规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> movesToStamp(string stamp, string target) {  // stamp 是印章，target 是目标串；返回每次盖章的起始下标序列，无解则返回空
        int m = stamp.size(), n = target.size();  // m 是印章长度，n 是目标串长度
        vector<int> indeg(n - m + 1, m);  // indeg[i]：以 i 为起点盖章时，还有多少个位置不匹配、需要被之前的某次盖章覆盖
        vector<int> g[n];  // g[p] 保存所有会覆盖到位置 p 的盖章起点
        queue<int> q;  // 入度为 0 的盖章起点，表示现在就能盖
        for (int i = 0; i < n - m + 1; ++i) {  // 枚举所有合法的盖章起点
            for (int j = 0; j < m; ++j) {  // 枚举印章的每一个字符
                if (target[i + j] == stamp[j]) {  // 该位置本来就与印章一致，不需要被覆盖
                    if (--indeg[i] == 0) {  // 匹配的位置不贡献入度；减到 0 说明此刻可以盖章
                        q.push(i);  // 所有位置都匹配，起点入队
                    }
                } else {  // 该位置不匹配，要靠之前某次覆盖到它的盖章来补齐
                    g[i + j].push_back(i);  // 把起点 i 登记到位置 i+j 的依赖表里
                }
            }
        }
        vector<int> ans;  // ans 逆序记录盖章的起点
        vector<bool> vis(n);  // vis[p]：目标串第 p 个位置是否已经被某次盖章覆盖成正确字符
        while (q.size()) {  // 队列非空就一直取「现在能盖」的起点
            int i = q.front();  // 取队首
            q.pop();  // 出队
            ans.push_back(i);  // 记录这次盖章
            for (int j = 0; j < m; ++j) {  // 这次盖章会覆盖 stamp 的每个位置
                if (!vis[i + j]) {  // 同一位置只需处理一次，重复覆盖不会带来新信息
                    vis[i + j] = true;  // 标记该位置已变正确
                    for (int k : g[i + j]) {  // 所有依赖这个位置的盖章起点，入度都可以减一
                        if (--indeg[k] == 0) {  // 入度减到 0，说明该起点现在也能盖了
                            q.push(k);  // 入队
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {  // 检查是否每个位置都被覆盖过
            if (!vis[i]) {  // 有位置始终不正确
                return {};  // 无解，按题目要求返回空数组
            }
        }
        reverse(ans.begin(), ans.end());  // 拓扑序是「最后盖的在前」，翻转后才是正向盖章顺序
        return ans;  // 返回盖章顺序
    }
};