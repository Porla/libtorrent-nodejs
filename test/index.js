var lt = require('../');
var assert = require('assert');

describe('libtorrent', function() {
    describe("add_torrent_params", function() {
        it("can get/set save path", function() {
            var params = new lt.add_torrent_params();
            params.save_path = "Foo";
            assert.equal("Foo", params.save_path);
        });
    });

    describe("bdecode", function() {
        it("can bdecode", function() {
            var node = lt.bdecode("li2ei3ee");
            assert.equal(node.type(), 2);
        });

        it("throws on invalid input", function() {
            assert.throws(function() { lt.bdecode("invalid input"); });
        });
    });

    describe("bdecode_node", function() {
        it("cannot be new'ed", function() {
            assert.throws(function() { new lt.bdecode_node(); });
        });

        it("cannot be func'ed", function() {
            assert.throws(function() { lt.bdecode_node(); });
        });

        it("has function dict_find_int_value", function() {
            var node = lt.bdecode("d3:fooi42ee");
            assert.equal(42, node.dict_find_int_value("foo"));
        });

        it("has function dict_find_string_value", function() {
            var node = lt.bdecode("d3:foo3:bare");
            assert.equal("bar", node.dict_find_string_value("foo"));
        });
    });

    describe("read_resume_data", function() {
        it("can read resume data", function() {
            var params = lt.read_resume_data("d9:save_path3:foo11:file-format22:libtorrent resume file12:file-versioni1e9:info-hash20:aaaabbbbccccddddeeefe");
            assert.equal(params.save_path, "foo");
        });
    });

    describe("session", function() {
        it("can add dht router", function() {
            var obj = new lt.session();
            obj.add_dht_router("router.bittorrent.com", 6881);
        });

        it("can load state", function() {
            var obj = new lt.session();
            obj.load_state(lt.bdecode("le"));
        });

        it("has function 'is_listening'", function() {
            var obj = new lt.session();
            assert.equal(typeof obj.is_listening(), 'boolean');
        });

        it("has function 'is_paused'", function() {
            var obj = new lt.session();
            assert.equal(typeof obj.is_paused(), 'boolean');
        });

        it("has function 'pop_alerts'", function() {
            var obj = new lt.session();
            assert.equal(Array.isArray(obj.pop_alerts()), true);
        });

        it("can wait for alert", function(done) {
            var obj = new lt.session();
            obj.wait_for_alert(10000, function(error, result) {
                assert.equal(result, true);
                done();
            });
        });
    });
});
