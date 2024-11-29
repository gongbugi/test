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
	printf("��� ���ϸ��� ���ðڽ��ϱ�?\n1. ���̸� 2. �̻��ؾ� 3. ���α�\n>>");
	scanf(" %d", &i);
	switch (i) {
	case 1:
		strcpy(m[0].name, "���̸�");
		strcpy(m[0].type, "��");
		m[0].power = 100 + rand() % 51;
		m[0].hp = m[0].nhp = 500 + rand() % 501;
		break;
	case 2:
		strcpy(m[0].name, "�̻��ؾ�");
		strcpy(m[0].type, "Ǯ");
		m[0].power = 100 + rand() % 51;
		m[0].hp = m[0].nhp = 500 + rand() % 501;
		break;
	case 3:
		strcpy(m[0].name, "���α�");
		strcpy(m[0].type, "��");
		m[0].power = 100 + rand() % 51;
		m[0].hp = m[0].nhp = 500 + rand() % 501;
		break;
	}
}
void shop()
{
	int i, d;
	printf("=======\n���� ���� �ݾ�: %d\n1.���ͺ�\t1000\n2.ȸ������\t2500\n", t.money);
	while (1) {
		printf("� �������� ��ðڽ��ϱ�?\n>>");
		scanf("%d", &i);
		if (i == 1) {
			printf("���� �Է�: ");
			scanf(" %d", &d);
			if (d * 1000 > t.money) {
				printf("���� �����Ͽ� �� �� �����ϴ�\n");
				continue;
			}
			printf("���������� ���ͺ��� �����Ͽ����ϴ�\n");
			t.money -= d * 1000;
			t.ball += d;
			printf("========\n���� ���� �ݾ�: %d\n", t.money);
		}
		else if (i == 2) {
			printf("���� �Է�: ");
			scanf("%d", &d);
			if (d * 2500 > t.money) {
				printf("���� �����Ͽ� �� �� �����ϴ�\n");
				continue;
			}
			printf("���������� ȸ�������� �����Ͽ����ϴ�\n");
			t.money -= d * 2500;
			t.heal += d;
			printf("========\n���� ���� �ݾ�: %d\n", t.money);
		}
		else
			break;
	}
}
int type(char my[], char wild[])
{
	if (strcmp(my, wild) == 0)
		return 0;
	else if (strcmp(my, "��") == 0 && strcmp(wild, "Ǯ") == 0 || strcmp(my, "��") == 0 && strcmp(wild, "��") == 0 || strcmp(my, "Ǯ") == 0 && strcmp(wild, "��") == 0)
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
	printf("�߻��� ���ϸ��� ��Ÿ����!\n%s\t%s\t%d/%d", wild[num].name, wild[num].type, wild[num].nhp, wild[num].hp);
	printf("\n����� ���ϸ��� ����\n=================\n");
	for (n = 0; n < t.mcount; n++)
		printf("%d. %s\t%s\t%d/%d\n", n + 1, m[n].name, m[n].type, m[n].nhp, m[n].hp);
	while (1) {
		scanf(" %d", &n);
		if (m[n - 1].nhp == 0) {
			printf("�� ���ϸ��� ������ �� �����ϴ�.\n");
			continue;
		}
		break;
	}
	while (1) {
		printf("1. �����ϱ� 2. ����ġ�� 3. ���� ����\n");
		scanf(" %d", &i);
		int chance = wild[num].nhp / wild[num].hp * 100;
		if (i == 1) {
			com = type(m[n - 1].type, wild[num].type);
			if (com == 1) {
				printf("ȿ���� �����ߴ�.\n");
				wild[num].nhp -= m[n - 1].power * 2;
				m[n-1].nhp -= wild[num].power / 2;
			}
			else if (com == -1) {
				printf("ȿ���� ������ �� �ϴ�.\n");
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
				printf("��븦 ����Ʈ�ȴ�!\n==========\n");
				break;
			}
			if (wild[num].nhp == 0) {
				printf("��! ���ϸ��� ���������ȴ�...\n==========\n");
				break;
			}
			if (m[n - 1].nhp <= 0) {
				t.amcount--;
				if (t.amcount == 0)
					break;
				printf("\n����� ���ϸ��� ����\n=================\n");
				for (n = 0; n < t.mcount; n++)
					printf("%d. %s\t%s\t%d/%d\n", n + 1, m[n].name, m[n].type, m[n].nhp, m[n].hp);
				while (1) {
					scanf(" %d", &n);
					if (m[n - 1].nhp == 0) {
						printf("�� ���ϸ��� ������ �� �����ϴ�.\n");
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
				printf("��������\n");
		}
		else {
			if (t.ball == 0 && t.heal == 0)
				printf("������ ����ֽ��ϴ�.\n");
			else {
				printf("==========\n1. ���� ��\tx%d\n2. ȸ�� ����\tx%d\n\n� �������� ����Ͻðڽ��ϱ�?:", t.ball, t.heal);
				scanf(" %d", &bag);
				if (bag == 1) {
					if (t.ball == 0)
						printf("���� ���� �����ϴ�.\n");
					else if (t.mcount == 6)
						printf("���̻� ���ϸ��� ���� �� �����ϴ�.\n");
					else {
						printf("���� ���ͺ�!\n");
						t.ball--;
						if (wild[num].nhp >= wild[num].hp / 2)
							printf("ü���� �� ����ּ���.\n");
						else {
							if (c_chance(chance)) {
								printf("���ϸ��� ��Ҵ�!\n");
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
								printf("���ϸ��� ���ͺ��� ���� ���Դ�.\n");
							}
						}
					}

				}
				else if (bag == 2) {
					if (t.heal == 0)
						printf("ȸ�� ������ �����ϴ�.\n");
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
			printf("�ȴ���\n==========\n");
			Sleep(1000 * (rand() % 4));
			encounter(m);
		}
		if(t.amcount == 0) {
			printf("�� ���� ����������.\n");
			printf("�����ϰ� ��� ��� ���ϸ��� ü���� ȸ���Ǿ����ϴ�.\n");
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
	printf("==========================\n\t���ϸ���\n press enter key to start\n==========================\n");
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
		printf("1.�����ϱ�\t2.�̾��ϱ�\n");
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
		printf("������ �����ðڽ��ϱ�?\n1. �� 2. �ƴϿ� 3. ��������\n>>");
		scanf(" %d", &i);
		if (i == 1) {
			walk(m);
		}
		if (i == 2) {
			printf("�����Ͻðڽ��ϱ�?\n1. �� 2. �ƴϿ�\n>>");
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