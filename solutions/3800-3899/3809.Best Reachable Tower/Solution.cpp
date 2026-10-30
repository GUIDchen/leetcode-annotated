// 3809. Best Reachable Tower | 最好可到达的塔
// 核心思路：枚举所有塔，用曼哈顿距离筛出半径内的候选，再按“质量更大优先、质量相同则坐标字典序更小优先”的规则维护最优下标。
// 复杂度：时间 O(n)（单次线性扫描）；空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<int> bestTower(vector<vector<int>>& towers, vector<int>& center, int radius) {  // 在曼哈顿距离不超过 radius 的塔中，返回质量最高（并列时坐标最小）的那座塔的坐标
        int cx = center[0], cy = center[1];  // 把中心点坐标拆成两个变量，避免循环里反复取下标
        int idx = -1;  // idx 记录当前最优塔的下标，-1 表示还没有候选项
        for (int i = 0; i < towers.size(); ++i) {  // 枚举每一座塔
            int x = towers[i][0], y = towers[i][1], q = towers[i][2];  // 取出该塔的坐标 (x, y) 与质量 q
            int dist = abs(x - cx) + abs(y - cy);  // 计算到中心点的曼哈顿距离
            if (dist > radius) {  // 超出可到达半径
                continue;  // 跳过这座塔
            }  // 结束半径判断
            if (  // 判断当前塔是否严格优于已知最优（多行条件开始）
                idx == -1  // 还没有任何候选，直接选中
                || towers[idx][2] < q  // 质量比最优更高
                || (towers[idx][2] == q && (x < towers[idx][0] || (x == towers[idx][0] && y < towers[idx][1])))) {  // 质量相同则比较坐标字典序：x 更小，或 x 相同而 y 更小
                idx = i;  // 更新最优下标
            }  // 结束更优判断
        }  // 枚举结束
        if (idx == -1) {  // 半径内一座塔都没有
            return {-1, -1};  // 按题意返回 {-1, -1}
        }  // 结束无解分支
        return {towers[idx][0], towers[idx][1]};  // 返回最优塔的坐标
    }  // 方法结束
};  // 类定义结束
