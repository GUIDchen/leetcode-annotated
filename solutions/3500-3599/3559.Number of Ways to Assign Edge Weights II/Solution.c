// 3559. 给边赋权值的方案数 II / Number of Ways to Assign Edge Weights II
// 核心思路：用倍增法预处理每个结点的祖先表与深度，对每个询问求出 u、v 的最近公共祖先并得到距离 d，答案为 2^(d-1)（d=0 时为 0）。
// 复杂度：预处理 O(n log n)，每次询问 O(log n)，空间 O(n log n)
int* assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize, int** queries,  // 返回每次询问的方案数数组，个数写入 returnSize
    int queriesSize, int* queriesColSize, int* returnSize) {  // queriesSize 个询问，queriesColSize 为列宽（未使用）
    int n = edgesSize + 1;  // 结点数等于边数加一
    int m = 32 - __builtin_clz(n);  // 倍增层数，即 log2(n) 向上取整
    int* cnt = calloc(n + 1, sizeof(int));  // 先用计数数组统计每个结点的度数
    for (int i = 0; i < edgesSize; ++i) {  // 遍历所有边累计度数
        ++cnt[edges[i][0]];  // 端点一度数加一
        ++cnt[edges[i][1]];  // 端点二度数加一
    }  // 结束度数统计
    int** g = malloc((n + 1) * sizeof(int*));  // 邻接表指针数组，下标从 1 开始
    for (int i = 1; i <= n; ++i) {  // 按度数逐个分配邻居数组
        g[i] = malloc(cnt[i] * sizeof(int));  // 分配结点 i 的邻居空间
        cnt[i] = 0;  // 计数清零，改用为写入下标
    }  // 结束空间分配
    for (int i = 0; i < edgesSize; ++i) {  // 再次遍历边，填充无向图
        int u = edges[i][0], v = edges[i][1];  // 取出边的两个端点
        g[u][cnt[u]++] = v;  // u 的邻居加入 v
        g[v][cnt[v]++] = u;  // v 的邻居加入 u
    }  // 结束建图
    int* f = calloc((n + 1) * m, sizeof(int));  // 倍增祖先表，按 f[结点 * m + 层] 平铺
    int* p = calloc(n + 1, sizeof(int));  // 每个结点的父结点，根的父结点为 0
    int* depth = calloc(n + 1, sizeof(int));  // 每个结点的深度，根为 0
    int* que = malloc(n * sizeof(int));  // BFS 队列，存放待处理结点
    int head = 0, tail = 0;  // 队列的首尾指针
    que[tail++] = 1;  // 根结点 1 入队
    while (head < tail) {  // 队列非空时逐层处理
        int i = que[head++];  // 取出队首结点 i
        f[i * m] = p[i];  // 第 0 层祖先就是父结点
        for (int j = 1; j < m; ++j) {  // 递推更高层的祖先
            f[i * m + j] = f[f[i * m + j - 1] * m + j - 1];  // 2^j 祖先等于 2^(j-1) 祖先的 2^(j-1) 祖先
        }  // 结束祖先递推
        for (int k = 0; k < cnt[i]; ++k) {  // 枚举结点 i 的所有邻居
            int j = g[i][k];  // 取出一个邻居 j
            if (j != p[i]) {  // 跳过父结点，只处理子结点
                p[j] = i;  // 记录 j 的父结点
                depth[j] = depth[i] + 1;  // 子结点深度加一
                que[tail++] = j;  // 子结点入队
            }  // 结束子结点判断
        }  // 结束邻居枚举
    }  // 结束 BFS
    const int mod = 1e9 + 7;  // 取模常量
    int* pow2 = malloc(n * sizeof(int));  // 预处理 2 的幂表
    pow2[0] = 1;  // 2 的 0 次方为 1
    for (int i = 1; i < n; ++i) {  // 递推填充幂表
        pow2[i] = pow2[i - 1] * 2 % mod;  // 前一项乘二再取模
    }  // 结束幂表构造
    int* ans = malloc(queriesSize * sizeof(int));  // 每个询问一个答案
    for (int t = 0; t < queriesSize; ++t) {  // 逐个处理询问
        int u = queries[t][0], v = queries[t][1];  // 取出询问的两个结点
        int x = u, y = v;  // 用副本向上跳，保留原来的深度值
        if (depth[x] < depth[y]) {  // 保证 x 是较深的那个结点
            int tmp = x;  // 借助临时变量交换
            x = y;  // x 换成较深结点
            y = tmp;  // y 换成较浅结点
        }  // 结束深度对齐前的交换
        for (int j = m - 1; j >= 0; --j) {  // 从高层到低层把 x 提到与 y 同深度
            if (depth[x] - depth[y] >= (1 << j)) {  // 跳 2^j 步仍不会越过 y
                x = f[x * m + j];  // x 向上跳 2^j 层
            }  // 结束这一步判断
        }  // 结束深度对齐
        for (int j = m - 1; j >= 0; --j) {  // 再从高层到低层同时上跳找分歧祖先
            if (f[x * m + j] != f[y * m + j]) {  // 两个祖先不同说明还没到 LCA
                x = f[x * m + j];  // x 上跳到该层祖先
                y = f[y * m + j];  // y 上跳到该层祖先
            }  // 结束这一步判断
        }  // 结束找 LCA 的上跳
        if (x != y) {  // 仍未相遇则 LCA 是当前 x 的父结点
            x = p[x];  // 走到真正的 LCA
        }  // 结束 LCA 修正
        int d = depth[u] + depth[v] - 2 * depth[x];  // 两点间边数等于深度和的二倍 LCA 深度修正
        ans[t] = d == 0 ? 0 : pow2[d - 1];  // 距离为 d 时方案数为 2^(d-1)，同一结点则为 0
    }  // 结束询问处理
    for (int i = 1; i <= n; ++i) {  // 释放每个结点的邻居数组
        free(g[i]);  // 释放结点 i 的邻居空间
    }  // 结束邻接表释放
    free(g);  // 释放邻接表指针数组
    free(cnt);  // 释放计数数组
    free(f);  // 释放倍增祖先表
    free(p);  // 释放父结点数组
    free(depth);  // 释放深度数组
    free(que);  // 释放 BFS 队列
    free(pow2);  // 释放幂表
    *returnSize = queriesSize;  // 写回答案个数
    return ans;  // 返回答案数组，由调用方释放
}  // 结束函数
