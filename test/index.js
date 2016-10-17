var fs = require('fs');
var lt = require('../');
var assert = require('assert');

function assertProperty(object, propertyName, testValue) {
    assert(propertyName in object, 'object does not contain property "' + propertyName + '"');
    object[propertyName] = testValue;
    assert.equal(testValue, object[propertyName]);
}

describe('libtorrent', function() {
    describe("add_torrent_params", function() {
        it("can get/set active time", function() {
            assertProperty(new lt.add_torrent_params(), 'active_time', 42);
        });

        it("can get/set added time", function() {
            assertProperty(new lt.add_torrent_params(), 'added_time', 42);
        });

        it("can get/set completed time", function() {
            assertProperty(new lt.add_torrent_params(), 'completed_time', 42);
        });

        it("can get/set download limit", function() {
            assertProperty(new lt.add_torrent_params(), 'download_limit', 42);
        });

        it("can get/set file priorities", function() {
            var p = new lt.add_torrent_params();
            assert('file_priorities' in p);

            p.file_priorities = [ 5, 10, 15 ];
            assert.deepEqual([ 5, 10, 15 ], p.file_priorities);
        });

        it("can get/set finished time", function() {
            assertProperty(new lt.add_torrent_params(), 'finished_time', 42);
        });

        it("can get/set save path", function() {
            assertProperty(new lt.add_torrent_params(), 'save_path', "foo");
        });

        it("can get/set torrent info", function() {
            var params = new lt.add_torrent_params();
            assert.equal(null, params.ti);

            params.ti = new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent");
            assert.equal("debian-8.5.0-amd64-netinst.iso", params.ti.name);
        });

        it("can get/set url", function() {
            assertProperty(new lt.add_torrent_params(), 'url', "foo");
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

    describe("torrent_info", function() {
        it("can be constructed from a 'bdecode_node'", function(done) {
            fs.readFile("res/debian-8.5.0-amd64-netinst.iso.torrent", (err, data) => {
                if (err) { throw err; }

                var node = lt.bdecode(data);
                var ti = new lt.torrent_info(node);
                assert.equal("debian-8.5.0-amd64-netinst.iso", ti.name);
                done();
            });
        });

        it("can be constructed from a path", function() {
            var ti = new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent");
            assert.equal("debian-8.5.0-amd64-netinst.iso", ti.name);
        });

        it("throws error when passed a non-existing path", function() {
            assert.throws(function() { new lt.torrent_info("non-existing path"); });
        });
    });
});
