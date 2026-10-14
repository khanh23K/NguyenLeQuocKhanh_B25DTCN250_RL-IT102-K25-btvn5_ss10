
#include <stdio.h>
#include <string.h>

#define MAX_TICKETS 5

// ==================== CAU TRUC DU LIEU ====================

struct Ticket {
    int ticket_id;
    char event_name[50];
    double price;
    int is_vip;  // 1: VIP, 0: Ve thuong
};

// ==================== FUNCTION PROTOTYPES ====================

double tinhGiaVe(double price, int is_vip);

int timVeTheoMa(const struct Ticket list[],
                int total_tickets, int ticket_id);

void hienThiDanhSach(const struct Ticket list[],
                     int total_tickets);

int themVe(struct Ticket list[], int total_tickets,
           struct Ticket veMoi);

int xoaVe(struct Ticket list[], int total_tickets,
          int ticket_id);


// ==================== HAM MAIN ====================

int main(void) {
    struct Ticket list[MAX_TICKETS] = {
        {101, "Concert Ha Noi", 500000.0, 1},
        {102, "Concert Da Nang", 400000.0, 0}
    };

    int total_tickets = 2;

    struct Ticket veMoi1 = {
        103, "Concert Sai Gon", 600000.0, 1
    };

    struct Ticket veMoi2 = {
        104, "Concert Hue", 350000.0, 0
    };

    struct Ticket veMoi3 = {
        105, "Concert Hai Phong", 450000.0, 1
    };

    struct Ticket veMoi4 = {
        106, "Concert Da Lat", 300000.0, 0
    };

    printf("============================================\n");
    printf("       HE THONG QUAN LY VE TICKETGO         \n");
    printf("============================================\n");

    // 1. Hien thi danh sach ban dau
    printf("\n========== 1. DANH SACH BAN DAU ==========\n");
    hienThiDanhSach(list, total_tickets);

    // 2. Tinh gia ve VIP
    printf("\n========== 2. TINH GIA VE VIP ==========\n");
    printf("Gia goc: %.0f VND\n", 500000.0);
    printf("Gia thanh toan VIP: %.0f VND\n",
           tinhGiaVe(500000.0, 1));

    // 3. Them ve moi
    printf("\n========== 3. THEM VE 103 ==========\n");
    total_tickets = themVe(list, total_tickets, veMoi1);
    printf("So luong ve hien tai: %d\n", total_tickets);

    printf("\n========== 4. THEM VE 104 ==========\n");
    total_tickets = themVe(list, total_tickets, veMoi2);
    printf("So luong ve hien tai: %d\n", total_tickets);

    printf("\n========== 5. THEM VE 105 ==========\n");
    total_tickets = themVe(list, total_tickets, veMoi3);
    printf("So luong ve hien tai: %d\n", total_tickets);

    // 4. Thu them khi mang da day
    printf("\n========== 6. KIEM TRA MANG DAY ==========\n");
    total_tickets = themVe(list, total_tickets, veMoi4);
    printf("So luong ve hien tai: %d\n", total_tickets);

    // 5. Xoa ma ve khong ton tai
    printf("\n========== 7. XOA VE KHONG TON TAI ==========\n");
    total_tickets = xoaVe(list, total_tickets, 999);
    printf("So luong ve hien tai: %d\n", total_tickets);

    // 6. Xoa mot ve hop le
    printf("\n========== 8. XOA VE 102 ==========\n");
    total_tickets = xoaVe(list, total_tickets, 102);
    printf("So luong ve hien tai: %d\n", total_tickets);

    // 7. Hien thi danh sach cuoi cung
    printf("\n========== 9. DANH SACH SAU CUNG ==========\n");
    hienThiDanhSach(list, total_tickets);

    printf("\nKet thuc chuong trinh!\n");

    return 0;
}


// ==================== HAM TINH GIA VE ====================

// VIP phu thu 20%, ve thuong giu nguyen gia
double tinhGiaVe(double price, int is_vip) {
    if (is_vip == 1) {
        return price * 1.2;
    }

    return price;
}


// ==================== HAM TIM KIEM ====================

// Tra ve vi tri neu tim thay, -1 neu khong tim thay
int timVeTheoMa(const struct Ticket list[],
                int total_tickets, int ticket_id) {
    int i;

    for (i = 0; i < total_tickets; i++) {
        if (list[i].ticket_id == ticket_id) {
            return i;
        }
    }

    return -1;
}


// ==================== HAM HIEN THI ====================

void hienThiDanhSach(const struct Ticket list[],
                     int total_tickets) {
    int i;
    double giaThanhToan;

    if (total_tickets == 0) {
        printf("Danh sach ve dang rong!\n");
        return;
    }

    printf("--------------------------------------------------------------------------\n");
    printf("%-5s %-25s %-15s %-12s %-15s\n",
           "MA VE", "TEN SU KIEN", "GIA GOC",
           "LOAI VE", "GIA THANH TOAN");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < total_tickets; i++) {
        giaThanhToan = tinhGiaVe(
            list[i].price, list[i].is_vip
        );

        printf("%-5d %-25s %-15.0f %-12s %-15.0f\n",
               list[i].ticket_id,
               list[i].event_name,
               list[i].price,
               list[i].is_vip == 1 ? "VIP" : "Thuong",
               giaThanhToan);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Tong so ve: %d/%d\n", total_tickets, MAX_TICKETS);
}


// ==================== HAM THEM VE ====================

// Tra ve so luong ve moi sau khi them
int themVe(struct Ticket list[], int total_tickets,
           struct Ticket veMoi) {
    int viTri;

    // Kiem tra danh sach da day
    if (total_tickets >= MAX_TICKETS) {
        printf("[LOI] Danh sach ve da day!\n");
        return total_tickets;
    }

    // Kiem tra du lieu dau vao
    if (veMoi.ticket_id <= 0 ||
        veMoi.event_name[0] == '\0' ||
        veMoi.price <= 0 ||
        (veMoi.is_vip != 0 && veMoi.is_vip != 1)) {
        printf("[LOI] Thong tin ve moi khong hop le!\n");
        return total_tickets;
    }

    // Kiem tra ma ve bi trung
    viTri = timVeTheoMa(list, total_tickets, veMoi.ticket_id);

    if (viTri != -1) {
        printf("[LOI] Ma ve %d da ton tai!\n", veMoi.ticket_id);
        return total_tickets;
    }

    // Them ve vao cuoi danh sach
    list[total_tickets] = veMoi;
    total_tickets++;

    printf("[THANH CONG] Da them ve %d!\n", veMoi.ticket_id);

    return total_tickets;
}


// ==================== HAM XOA VE ====================

// Tra ve so luong ve moi sau khi xoa
int xoaVe(struct Ticket list[], int total_tickets,
          int ticket_id) {
    int viTri;
    int i;

    // Kiem tra danh sach rong
    if (total_tickets == 0) {
        printf("[LOI] Danh sach ve dang rong!\n");
        return total_tickets;
    }

    // Su dung lai ham tim kiem
    viTri = timVeTheoMa(list, total_tickets, ticket_id);

    if (viTri == -1) {
        printf("[LOI] Khong tim thay ma ve %d!\n", ticket_id);
        return total_tickets;
    }

    // Don cac phan tu phia sau sang trai
    for (i = viTri; i < total_tickets - 1; i++) {
        list[i] = list[i + 1];
    }

    total_tickets--;

    printf("[THANH CONG] Da xoa ve %d!\n", ticket_id);

    return total_tickets;
}

