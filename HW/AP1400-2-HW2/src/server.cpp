#include "server.h"
using std::runtime_error;
/***
 *std::random_device only works on linux system.
 */
std::map<std::shared_ptr<Client>, double> Server::get_clients() const { return this->clients; }
std::vector<std::string> pending_trxs = {};

void show_wallets(const Server& server) {
    std::cout << std::string(20, '*') << std::endl;
    for (const auto& client : server.get_clients())
        std::cout << client.first->get_id() << " : " << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}

Server::Server() { this->clients = {}; }

std::string produceRandom() {
    std::string res = "";
    // std::default_random_engine engine;
    // std::uniform_int_distribution<int> distribution(1, 10);
    // std::random_device rd;
    for (int i = 0; i < 4; i++) {
        auto num = e() % 10;
        res += std::to_string(num);
    }
    return res;
}

std::shared_ptr<Client> Server::add_client(std::string id) {
    auto isExist{false};
    for (auto& [client, amount] : clients) {
        if (client->get_id() == id) {
            isExist = true;
            break;
        }
    }

    std::string newID = id;
    if (isExist) {
        newID = id + produceRandom();
    }
    Client* newClient = new Client(newID, *this);
    std::shared_ptr<Client> sp(newClient);
    this->clients[sp] = 5;
    return sp;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (auto& [k, v] : clients) {
        if (k->get_id() == id) {
            return k;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) {
    auto sp = get_client(id);
    if (sp == nullptr) {
        return 0;
    }
    return this->clients[sp];
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    int p = 0;
    int mark[] = {0, 0};
    for (int i = 0; i < trx.length(); i++) {
        if (trx.at(i) == '_' || (p >= 2 && trx.at(i) == '-')) {
            throw runtime_error("something bad");
            return false;
        }
        if (trx.at(i) == '-') {
            mark[p] = i;
            p++;
        }
    }
    auto mark2 = mark[1];
    auto mark1 = mark[0];

    sender = trx.substr(0, mark1);
    receiver = trx.substr(mark1 + 1, mark2 - mark1 - 1);
    value = std::stod(trx.substr(mark2 + 1, trx.length()));
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) {
    std::string sender{};
    std::string receiver{};
    double value = 0;
    try {
        parse_trx(trx, sender, receiver, value);
    } catch (runtime_error e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    pending_trxs.push_back(trx);
    // cout << "value = " << value << endl << "get_wallet = " << get_wallet(sender) << endl;

    if (get_wallet(sender) < value) {
        return false;
    }

    this->clients[this->get_client(sender)] -= value;
    this->clients[this->get_client(receiver)] += value;

    return true;
}

size_t Server::mine() {
    // std::random_device d;
    // if (pending_trxs.size() == 0) {
    //     return d();
    // }
    // std::string mempool{};
    // for (auto trx : pending_trxs) {
    //     mempool += trx;
    // }
    // auto end{false};
    // while (!end) {
    //     for (auto& [k, _] : clients) {
    //         auto nonce = k->generate_nonce();
    //         auto m = mempool + std::to_string(nonce);
    //         auto sha = crypto::sha256(m);
    //         if (sha.substr(0, 10).find("000") != std::string::npos) {
    //             clients[k] += 6.25;
    //             for (auto trx : pending_trxs) {
    //                 std::string sender{}, receiver{};
    //                 double value;
    //                 parse_trx(trx, sender, receiver, value);
    //                 clients[get_client(sender)] -= value;
    //                 clients[get_client(receiver)] += value;
    //             }
    //             pending_trxs.clear();
    //             end = true;
    //             return nonce;
    //         }
    //     }
    // }
    // return d();

    // std::random_device rd;
    if (pending_trxs.size() == 0) {
        return e() % 10;
    }

    std::string mempool = "";
    for (int i = 0; i < pending_trxs.size(); i++) {
        mempool += pending_trxs[i];
    }

    cout << mempool << endl;

    std::string id = "";
    size_t n = 0;
    for (auto& [k, v] : clients) {
        auto nonce = k->generate_nonce();
        std::string str = mempool + std::to_string(nonce);
        std::string hash{crypto::sha256(str)};
        if (hash.substr(0, 10).find("000") != std::string::npos) {
            std::cout << k->get_id() << std::endl;
            v += 6.5;
            pending_trxs.clear();
            return nonce;
        }
    }
    for (int i = 0; i < 10; i++) {
        std::string str = mempool + std::to_string(i);
        std::string hash{crypto::sha256(str)};
        if (hash.substr(0, 10).find("000") != std::string::npos) {
            return i;
        }
    }
    return e() % 10;
}