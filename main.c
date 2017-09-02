#include <stdio.h>
#include <stdlib.h>

struct Seed {
    int num;
    struct Seed *ySeed;
    struct Seed *nSeed;
};

const int Q_NUM = 10;
char a[20];
int i;
char q[2][20][100];

void wriFi(int b, char c[20]) {
    FILE *fp;
    fp = fopen("hoge.txt", "w");
    fprintf(fp, "%d %s ", b, c);
    fclose(fp);
}

void readFi(int b) {
    FILE *fp;
    fp = fopen("hoge.txt", "r");
    char a_[20];
    char c[20];
    while ((fscanf(fp, "%s", a) != EOF)) {
        fscanf(fp, "%s", a_);
        for (i = 0; i < 20; i++) {
            if (a[i] == '\n') {
                c[i] = '\0';
                break;
            }
            c[i] = a[i];
        }
        if (atoi(c) == b) {
            printf("%s\n", a_);
        }
    }
    fclose(fp);
}

int question(int k) {
    printf("%s Y/N\n", q[0][k]);
    scanf("%s", a);
    return (a[0] == 'Y' || a[0] == 'y');
}

void regiBody(char a_[20], int k, struct Seed *next) {
    if (k == Q_NUM) {
        wriFi(next->num, a_);
        return;
    }
    if (question(k)) {
        regiBody(a_, k + 1, next->ySeed);
    } else {
        regiBody(a_, k + 1, next->nSeed);
    }
    return;
}

void searBody1(struct Seed *s, int num, int *q_) {
    if (num == Q_NUM) {
        readFi(s->num);
        return;
    }
    if (q_[num] != 1) {
        searBody1(s->nSeed, num + 1, q_);
    } else if (q_[num] != 0) {
        searBody1(s->ySeed, num + 1, q_);
    }
    return;
}

void searBody0(struct Seed *s, int num, int *q_) {
    if (num == Q_NUM) {
        printf("ちょっと探してきますね・・・\n");
        searBody1(s, 0, q_);
        printf("私が知っているなかで特徴に当てはまる人を探してきました.\nどうでしょうか？わたし，役に立てましたか？！\n");
        return;
    }
    printf("%s Y/N/?(I don't know.)\n", q[1][num]);
    scanf("%s", a);
    q_[num] = 2;
    if (a[0] == 'Y' && a[0] == 'y') {
        q_[num] = 1;
    } else if (a[0] == 'N' && a[0] == 'n') {
        q_[num] = 0;
    }
    searBody0(s, num + 1, q_);
    return;
}

void memInit(struct Seed *s, int num, int k) {
    struct Seed *y;
    struct Seed *n;
    y = (struct Seed *) malloc(sizeof(struct Seed));
    n = (struct Seed *) malloc(sizeof(struct Seed));
    s->ySeed = y;
    s->nSeed = n;
    s->num = 0;
    if (num < Q_NUM) {
        memInit(y, num + 1, k * 2 + 1);
        memInit(n, num + 1, k * 2 + 2);
    } else {
        s->num = k;
    }
    return;
}

int init() {
    printf("利用するのは初めてですかっ?\nY/N\n");
    scanf("%s", a);
    return (a[0] == 'Y' || a[0] == 'y');
}

void sear(struct Seed *s) {
    printf("人探しですか？ Y/N\n");
    scanf("%s", a);
    int q_[20];
    if (a[0] == 'Y' || a[0] == 'y') {
        printf("了解！まかせてください!\n探してくるので今からその人の特徴を教えてください!\n");
        searBody0(s, 0, q_);
    } else {
        printf("そうですか・・・眠いのでおやすみなのです。\n");
        return;
    }
    while (1) {
        printf("まだ人探ししますか??\n");
        scanf("%s", a);
        if (a[0] != 'Y' && a[0] != 'y') {
            printf("そうですか・・・眠いのでおやすみなのです。\n");
            return;
        } else {
            printf("了解!まかせてください!\n探してくるので今からその人の特徴を教えてください.\n");
            searBody0(s, 0, q_);
        }
    }
}

void regi(struct Seed *first) {
    printf("初めまして！私は、Nanです！\nあなたのお名前を教えてください。\n名前 : ");
    char a_[20];
    scanf("%s", a_);
    regiBody(a_, 0, first);
    printf("ありがとう!無事あなたの事を知れたぞい!これからよろしく%sさん!", a_);
}


int main() {
    struct Seed *seed;
    seed = (struct Seed *) malloc(sizeof(struct Seed));
    memInit(seed, 0, 0);
    if (init()) {
        regi(seed);
    }
    sear(seed);
    return 0;
}