#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAKS 255

typedef struct simpul Node;
typedef struct simpulMk MK;

struct simpul {
    int nrp;
    char nama[MAKS];
    char prodi[MAKS];
    Node *next;
    Node *prev;
    Node *mk;
};

struct simpulMk {
    char kode[MAKS];
    char namaMk[MAKS];
    float nilai;
    MK *nextMk;
};

Node *head = NULL;
Node *tail= NULL;
Node *baru;

MK *baruMk;

void clean_stdin(void)
{
    int c;
    do{ c = getchar(); } while (c != '\n' && c != EOF);
}

void allocate_node(int x, char y[], char z[]){
    baru=(Node *) malloc (sizeof(Node));
    if(baru==NULL){
        printf("Pengalokasian memori gagal\n");
        exit(1);}
    else{
        baru->nrp = x;
        strcpy(baru->prodi, y);
        strcpy(baru->nama, z);
        baru->next = NULL;
        baru->prev = NULL;
        baru->mk = NULL;
    }
}

void allocate_mk(char kode[], char namaMk[], float nilai)
{
    baruMk = (MK *) malloc(sizeof(MK));
    if (baruMk==NULL)
    {
        printf("Alokasi gagal\n");
        exit (1);
    }
    else
    {
        strcpy(baruMk->kode, kode);
        strcpy(baruMk->namaMk, namaMk);
        baruMk->nilai = nilai;
        baruMk->nextMk = NULL;
    }
}

void sisip_awal()
{
    if(head==NULL)
    {
        head=tail=baru;
    }
    else{
        baru->next=head;
        head->prev=baru;
        head=baru;
    }
}

void sisip_akhir()
{
    baru->prev=tail;
    tail->next=baru;
    tail=baru;
}

void sisip_sebelum(int x)
{
    Node *before=head;
    if(head->nrp==x)
        sisip_awal();
    else{
        while(before!=NULL && before->nrp != x)
            before = before->next;

        if(before==NULL) printf("Simpul tidak ada\n");
        else{
            baru->prev = before->prev;
            baru->next = before;
            before->prev->next = baru;
            before->prev = baru;
        }
    }
}

void sisip_setelah(int x)
{
    Node *after = tail;
    if(tail->nrp==x)
        sisip_akhir();
    else{
        while (after->prev!=NULL && after->nrp!= x)
            after = after->prev;

        if(after==NULL) printf("Simpul tidak ada\n");
        else{
            baru->prev = after;
            baru->next = after->next;
            after->next->prev = baru;
            after->next = baru;
        }
    }
}

void free_Node(Node *p)
{
    free(p);
    p=NULL;
}

void free_MK(MK *p)
{
    free(p);
    p=NULL;
}

void hapus_awal(){
    Node *hapus = head;
    head->prev=NULL;
    head = hapus->next;
    free_Node(hapus);
}

void hapus_akhir(){
    Node *hapus=tail;
    tail->prev->next=NULL;
    hapus->prev=tail;
    free_Node(hapus);
}

void hapus_tengah(int x){
    Node *hapus, *before;
    hapus=before=head;
    if(hapus==NULL)
        printf("Data kosong");
    else if(hapus->nrp==x)
    {
        hapus_awal();
    }
    else{
        while(hapus!=NULL && hapus->nrp != x){
            hapus = hapus->next;
        }
        if(hapus==NULL)
            printf("data tidak ada\n");
        else{
            hapus->prev->next = hapus->next;
            hapus->next->prev=hapus->prev;
            free_Node(hapus);
        }
    }
}

void sisip(){
    Node *before = head;
    if (head==NULL)
        head=tail=baru;
    else if (head->nrp>baru->nrp)
        sisip_awal();
    else{
        Node *before=head;
        while(before!=NULL&&before->nrp<baru->nrp){
            before=before->next;
        }
        if(before==NULL)
            sisip_akhir();
        else if(before->nrp==baru->nrp)
            printf("ERROR, NRP yang anda masukkan sudah digunakan\n");
        else
            sisip_sebelum(before->nrp);
    }
}

void sisip_mk(int x){
    Node *mhs=head;
    if(mhs==NULL)
    {
        printf("Data Kosong\n");
    }
    else{
        while(mhs!=NULL && mhs->nrp!=x){
            mhs=mhs->next;
        }
        if(mhs==NULL){
            printf("Data Tidak Ada\n");
        }
        else if(mhs->mk==NULL){
            mhs->mk=baruMk;
            baruMk->nextMk=NULL;
        }
        else{
            MK *mk_mhs=mhs->mk;
            while(mk_mhs->nextMk!=NULL)
                mk_mhs=mk_mhs->nextMk;
            mk_mhs->nextMk=baruMk;
            baruMk->nextMk=NULL;
        }
    }
}

void hapuss(int x)
{
    Node *hapus, *before;
    hapus=before=head;
    if(hapus==NULL){
        printf("Data Kosong\n");
    }
    else if (hapus->nrp==x){
        hapus_awal();
    }
    else{
        while (hapus!=NULL && hapus->nrp!=x){
            before=hapus;
            hapus=hapus->next;
        }
        if (hapus==NULL)
            printf("Data tidak ada\n");
        else{
            before->next=hapus->next;
            free_Node(hapus);
        }
    }
}

void hapus_mk(int x, char mk[])
{
    Node *mhs=head;
    MK *hapus, *before;

    while(mhs!=NULL && mhs->nrp!=x){
        mhs=mhs->next;
    }
    if (mhs == NULL){
        printf("Mahasiswa yang dipilih tidak ada\n\n");
    } else {
        MK *mk_mhs=mhs->mk; // ambil node mk dari mahasiswa yang dipilih
        hapus=before=mhs->mk;
        if(hapus==NULL)
        {
            printf("Data matkul mahasiswa masih kosong\n");
        }
        else if(strcmp(hapus->kode, mk)==0){
            mhs->mk=hapus->nextMk;
            free_MK(hapus);
        }
        else
        {
            while(hapus!=NULL && hapus->kode!=mk){
                before=hapus;
                hapus=hapus->nextMk;
            }
            if(hapus==NULL)printf("Data matkul mahasiswa tidak ada\n");
            else{
                before->nextMk=hapus->nextMk;
                free_MK(hapus);
            }
        }
    }
}

void update(int x, char y[], char z[]){
    Node *update;
    update=head;
    if(update==NULL)
    printf("Data Kosong");
    else{
        while(update!=NULL && update->nrp!=x){
        update=update->next;
        }
        if(update==NULL){
            printf("Data Tidak Ada");
        }
        else{
            strcpy(update->nama, z);
            strcpy(update->prodi, y);
        }
    }
}

float rata()
{
    Node *p=head;
    float jum=0, rata=0;
    int i=0;
    /*while(p!=NULL){
        i++;
        jum+=p->nilai;
        rata=jum/i;
        p=p->next;
    }*/
    return rata;
}

void cetak()
{
    Node *p=head;
    int i = 0;
    printf("+----------------+------------------------------------+---------------------+\n");
    printf("| NRP            | Nama                               | Prodi               |\n");
    printf("+----------------+------------------------------------+---------------------+\n");
    if (p==NULL){
    printf("| Tidak ada data mahasiswa yang dapat ditampilkan                           |\n");
    }
    while(p!=NULL){
        printf("| %-15d| %-35s| %-20s|\n", p->nrp, p->nama, p->prodi);
        p=p->next;
        i++;
    }
    printf("+----------------+------------------------------------+---------------------+\n");
}

void cetak_mh_mk()
{
    Node *p=head;
    MK *mk;
    float jml=0, rata=0, banyak=0;
    int i = 0;
    printf("+----------------+------------------------------------+----------------------------------------------+\n");
    printf("| NRP            | Nama                               | Prodi                                        |\n");
    printf("+----------------+------------------------------------+----------------------------------------------+\n");
    if (p==NULL){
    printf("| Tidak ada data mahasiswa yang dapat ditampilkan                                                    |\n");
    printf("+----------------+------------------------------------+----------------------------------------------+\n");
    }
    while(p!=NULL){
        jml=0, rata=0, banyak=0;
        printf("| %-15d| %-35s| %-45s|\n", p->nrp, p->nama, p->prodi);
        printf("+----------------+----------------+----------------------------------------------------+-------------+\n");
        printf("|                | Kode           | Nama Matkul                                        | Nilai       |\n");
        printf("|  DATA MATKUL   +----------------+----------------------------------------------------+-------------+\n");
        // mtkul=50
        mk=p->mk;
        if (mk==NULL){
            printf("|                | Tidak ada data matakuliah yang dapat ditampilkan                                  |\n");
        }
        while (mk!=NULL){
        printf("|%16s| %-15s| %-51s| %-12.2f|\n", " ", mk->kode, mk->namaMk, mk->nilai);
            banyak++; jml+=mk->nilai;
            mk=mk->nextMk;
        }

        rata=jml/banyak;
        printf("+----------------+----------------+----------------------------------------------------+-------------+\n");
        printf("|                                                                                      | Rata-rata   |\n");
        printf("+----------------+----------------+----------------------------------------------------+-------------+\n");
        if (p->mk!=NULL)
        printf("|                                                                                      | %-12.2f|\n", rata);
        else
        printf("|                                                                                      | %-12d|\n", 0);
        printf("+----------------+----------------+---------------+------------------------------------+-------------+\n");
        p=p->next;
        i++;
    }
}

int main()
{
    float k;
    int p, pilih, nrp, kode;
    float nilai;
    char nama[MAKS], prodi[MAKS], namaMk[MAKS], kodeMk[MAKS];
    char lagi='y';

    printf("+----------------------------------------------+\n");
    printf("|           PROGRAM MULTI LINKED LIST          |\n");
    printf("|                   MAHASISWA                  |\n");
    printf("+----------------------------------------------+\n\n");

    while(lagi=='y'){
        printf("1. Sisip Mahasiswa\n");
        printf("2. Hapus Mahasiswa\n");
        printf("3. Ubah Mahasiswa\n");
        printf("4. Sisip Matakuliah Mahasiswa\n");
        printf("5. Hapus Matakuliah Mahasiswa\n");
        printf("6. Lihat Mahasiswa dan Matakuliah\n");

        printf("\n");
        printf("Pilihan : "); scanf("%d", &pilih);
        printf("\n");
        clean_stdin();

        switch (pilih){
        case 1:
                printf("Masukkan NRP   : ");scanf("%d", &nrp);clean_stdin();
                printf("Masukkan Nama  : ");gets(&nama);
                printf("Masukkan Prodi : ");gets(&prodi);
                allocate_node(nrp, prodi, nama);
                sisip();
                printf("\n");cetak();printf("\n");
                break;
        case 2:
                cetak();
                printf("| Masukkan nrp yang ingin dihapus : ");scanf("%d", &p);
                clean_stdin();
                hapuss(p);
                printf("\n");cetak();printf("\n");
                break;
        case 3:
                printf("Masukkan NRP   : "); scanf("%d",&nrp);clean_stdin();
                printf("Masukkan Nama  : "); gets(&nama);
                printf("Masukkan Prodi : "); gets(&prodi);
                update(nrp , prodi, nama);
                printf("\n");cetak();printf("\n");
                break;
        case 4:
                printf("Masukkan NRP : "); scanf("%d", &nrp);clean_stdin();
                printf("Masukkan Kode Matakuliah : "); gets(&kodeMk);
                printf("Masukkan Nama Matakuliah : "); gets(&namaMk);
                printf("Masukkan Nilai : "); scanf("%f",&nilai);clean_stdin();
                allocate_mk(kodeMk, namaMk, nilai);
                sisip_mk(nrp);
                cetak_mh_mk();printf("\n");
                break;
        case 5:
                printf("Masukkan NRP         : "); scanf("%d", &nrp);clean_stdin();
                printf("Masukkan Kode Matkul : "); gets(&kodeMk);
                hapus_mk(nrp, kodeMk);
                cetak_mh_mk();printf("\n");
                break;
        case 6:
                cetak_mh_mk();
                break;
        default:
                printf("Menu pilihan anda tidak ada\n");
                break;
        }

        printf("Lagi ? (y/t) : ");
        scanf("%c", &lagi);
        clean_stdin();printf("\n");
    }
}
