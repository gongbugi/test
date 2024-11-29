#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
typedef struct {
	char name[20];
	char type[5];
	int power;
	int nhp;
	int hp;
}minfo;
typedef struct {
	int money;
	int ball;
	int heal;
	int mcount;
	int amcount;
}item;
item t;
void new(minfo *m)
{
	int i;
	printf("어느 포켓몬을 고르시겠습니까?\n1. 파이리 2. 이상해씨 3. 꼬부기\n>>");
	scanf(" %d", &i);
	switch (i) {
	case 1:
		strcpy(m[0].name, "파이리");
		strcpy(m[0].type, "불");
		m[0].power = 100 + rand() % 51;
		m[0].hp = m[0].nhp = 500 + rand() % 501;
		break;
	case 2:
		strcpy(m[0].name, "이상해씨");
		strcpy(m[0].type, "풀");
		m[0].power = 100 + rand() % 51;
		m[0].hp = m[0].nhp = 500 + rand() % 501;
		break;
	case 3:
		strcpy(m[0].name, "꼬부기");
		strcpy(m[0].type, "물");
		m[0].power = 100 + rand() % 51;
		m[0].hp = m[0].nhp = 500 + rand() % 501;
		break;
	}
}
void shop()
{
	int i, d;
	printf("=======\n현재 소유 금액: %d\n1.몬스터볼\t1000\n2.회복물약\t2500\n", t.money);
	while (1) {
		printf("어떤 아이템을 사시겠습니까?\n>>");
		scanf("%d", &i);
		if (i == 1) {
			printf("수량 입력: ");
			scanf(" %d", &d);
			if (d * 1000 > t.money) {
				printf("돈이 부족하여 살 수 없습니다\n");
				continue;
			}
			printf("성공적으로 몬스터볼을 구매하였습니다\n");
			t.money -= d * 1000;
			t.ball += d;
			printf("========\n현재 소유 금액: %d\n", t.money);
		}
		else if (i == 2) {
			printf("수량 입력: ");
			scanf("%d", &d);
			if (d * 2500 > t.money) {
				printf("돈이 부족하여 살 수 없습니다\n");
				continue;
			}
			printf("성공적으로 회복물약을 구매하였습니다\n");
			t.money -= d * 2500;
			t.heal += d;
			printf("========\n현재 소유 금액: %d\n", t.money);
		}
		else
			break;
	}
}
int type(char my[], char wild[])
{
	if (strcmp(my, wild) == 0)
		return 0;
	else if (strcmp(my, "불") == 0 && strcmp(wild, "풀") == 0 || strcmp(my, "물") == 0 && strcmp(wild, "불") == 0 || strcmp(my, "풀") == 0 && strcmp(wild, "물") == 0)
		return 1;
	else
		return -1;
}
int escape(int chance)
{
	if (chance == 100)
		return rand() % 10 > 8;
	else if (chance < 100 && chance >= 50)
		return rand() % 10 > 5;
	else if (chance < 50 && chance >= 25)
		return rand() % 10 > 2;
	else
		return rand() % 10 > 0;
}
int c_chance(int chance)
{
	if (chance >= 30)
		return rand() % 10 > 6;
	else if (chance < 30 && chance >= 10)
		return rand() % 10 > 3;
	else
		return rand() % 10 > 0;
}
void encounter(minfo* m)
{
	int i, n, com, bag;
	FILE* fp = fopen("pokemon_list.txt", "r");
	minfo wild[6];
	for (int i = 0; i < 6; i++) {
		fscanf(fp, "%s %s", wild[i].name, wild[i].type);
		wild[i].power = 100 + rand() % 101;
		wild[i].hp = wild[i].nhp = 500 + rand() % 701;
	}
	fclose(fp);
	int num = 0;
	printf("야생의 포켓몬이 나타났다!\n%s\t%s\t%d/%d", wild[num].name, wild[num].type, wild[num].nhp, wild[num].hp);
	printf("\n상대할 포켓몬을 선택\n=================\n");
	for (n = 0; n < t.mcount; n++)
		printf("%d. %s\t%s\t%d/%d\n", n + 1, m[n].name, m[n].type, m[n].nhp, m[n].hp);
	while (1) {
		scanf(" %d", &n);
		if (m[n - 1].nhp == 0) {
			printf("이 포켓몬은 출전할 수 없습니다.\n");
			continue;
		}
		break;
	}
	while (1) {
		printf("1. 공격하기 2. 도망치기 3. 가방 열기\n");
		scanf(" %d", &i);
		int chance = wild[num].nhp / wild[num].hp * 100;
		if (i == 1) {
			com = type(m[n - 1].type, wild[num].type);
			if (com == 1) {
				printf("효과는 굉장했다.\n");
				wild[num].nhp -= m[n - 1].power * 2;
				m[n-1].nhp -= wild[num].power / 2;
			}
			else if (com == -1) {
				printf("효과가 별로인 듯 하다.\n");
				wild[num].nhp -= m[n-1].power / 2;
				m[n - 1].nhp -= wild[num].power * 2;
			}
			else {
				wild[num].nhp -= m[n-1].power;
				m[n - 1].nhp -= wild[num].power;
			}
			printf("%s\t%s\t%d/%d\n", m[n-1].name, m[n-1].type, m[n-1].nhp, m[n-1].hp);
			printf("%s\t%s\t%d/%d\n", wild[num].name, wild[num].type, wild[num].nhp, wild[num].hp);
			if (wild[num].nhp < 0) {
				printf("상대를 쓰러트렸다!\n==========\n");
				break;
			}
			if (wild[num].nhp == 0) {
				printf("앗! 포켓몬이 도망가버렸다...\n==========\n");
				break;
			}
			if (m[n - 1].nhp <= 0) {
				t.amcount--;
				if (t.amcount == 0)
					break;
				printf("\n상대할 포켓몬을 선택\n=================\n");
				for (n = 0; n < t.mcount; n++)
					printf("%d. %s\t%s\t%d/%d\n", n + 1, m[n].name, m[n].type, m[n].nhp, m[n].hp);
				while (1) {
					scanf(" %d", &n);
					if (m[n - 1].nhp == 0) {
						printf("이 포켓몬은 출전할 수 없습니다.\n");
						continue;
					}
					break;
				}
			}
		}
		else if (i == 2) {
			if (escape(chance))
				break;
			else
				printf("도망실패\n");
		}
		else {
			if (t.ball == 0 && t.heal == 0)
				printf("가방이 비어있습니다.\n");
			else {
				printf("==========\n1. 몬스터 볼\tx%d\n2. 회복 물약\tx%d\n\n어떤 아이템을 사용하시겠습니까?:", t.ball, t.heal);
				scanf(" %d", &bag);
				if (bag == 1) {
					if (t.ball == 0)
						printf("몬스터 볼이 없습니다.\n");
					else if (t.mcount == 6)
						printf("더이상 포켓몬을 잡을 수 없습니다.\n");
					else {
						printf("가랏 몬스터볼!\n");
						t.ball--;
						if (wild[num].nhp >= wild[num].hp / 2)
							printf("체력을 더 깍아주세요.\n");
						else {
							if (c_chance(chance)) {
								printf("포켓몬을 잡았다!\n");
								t.amcount++;
								t.mcount++;
								strcpy(m[t.mcount - 1].name, wild[num].name);
								strcpy(m[t.mcount - 1].type, wild[num].type);
								m[t.mcount - 1].power = wild[num].power;
								m[t.mcount - 1].hp = wild[num].hp;
								m[t.mcount - 1].nhp = wild[num].nhp;
								break;
							}
							else {
								printf("포켓몬이 몬스터볼을 빠져 나왔다.\n");
							}
						}
					}

				}
				else if (bag == 2) {
					if (t.heal == 0)
						printf("회복 물약이 없습니다.\n");
					else {
						m[n - 1].nhp += m[n - 1].hp * 0.3;
						if (m[n - 1].nhp > m[n - 1].hp)
							m[n - 1].nhp = m[n - 1].hp;
						t.heal--;
					}
				}
			}
		}
	}
}
void walk(minfo* m)
{
	while (1) {
		if (t.amcount > 0) {
			printf("걷는중\n==========\n");
			Sleep(1000 * (rand() % 4));
			encounter(m);
		}
		if(t.amcount == 0) {
			printf("눈 앞이 깜깜해졌다.\n");
			printf("보유하고 계신 모든 포켓몬의 체력이 회복되었습니다.\n");
			for (int i = 0; i < t.mcount; i++)
				m[i].nhp = m[i].hp;
			t.amcount = t.mcount;
			break;
		}
	}
}
int main()
{
	char c = ' ';
	int i, p;
	minfo m[6];
	srand(time(NULL));
	printf("==========================\n\t포켓몬스터\n press enter key to start\n==========================\n");
	while (1) {
		scanf("%c", &c);
		if (c == '\n')
			break;
	}
	FILE* fp = fopen("user.txt", "r");
	if (fp == NULL) {
		new(m);
		t.money = 10000;
		t.ball = 0;
		t.heal = 0;
		t.mcount = 1;
		t.amcount = 1;
	}
	else {
		printf("1.새로하기\t2.이어하기\n");
		scanf(" %d", &i);
		if (i == 1) {
			new(m);
			t.money = 10000;
			t.ball = 0;
			t.heal = 0;
			t.mcount = 1;
			t.amcount = 1;
			fclose(fp);
		}
		else {
			fscanf(fp, "%d %d %d %d %d\n", &t.mcount, &t.amcount, &t.ball, &t.heal, &t.money);
			for (int j = 0; j < t.mcount; j++)
				fscanf(fp, "%s %s %d %d %d\n", m[j].name, m[j].type, &m[j].nhp, &m[j].hp, &m[j].power);
			fclose(fp);
		}
	}
	while (1) {
		printf("여행을 떠나시겠습니까?\n1. 네 2. 아니요 3. 상점가기\n>>");
		scanf(" %d", &i);
		if (i == 1) {
			walk(m);
		}
		if (i == 2) {
			printf("저장하시겠습니까?\n1. 네 2. 아니요\n>>");
			scanf(" %d", &p);
			if (p == 1) {
				FILE* fp = fopen("user.txt", "w");
				fprintf(fp, "%d %d %d %d %d\n", t.mcount, t.amcount, t.ball, t.heal, t.money);
				for (int j = 0; j < t.mcount; j++)
					fprintf(fp, "%s %s %d %d %d\n", m[j].name, m[j].type, m[j].nhp, m[j].hp, m[j].power);
				fclose(fp);
				return 0;
			}
			else
				return 0;
		}
		if (i == 3)
			shop();
	}
	return 0;
}