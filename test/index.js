var fs = require('fs');
var lt = require('../');
var assert = require('assert');

function assertProperty(object, propertyName, testValue) {
    assert(propertyName in object, 'object does not contain property "' + propertyName + '"');
    object[propertyName] = testValue;
    assert.equal(testValue, object[propertyName]);
}

describe('libtorrent', function() {
    describe("bdecode", function() {
        it("can bdecode string", function() {
            var node = lt.bdecode("li2ei3ee");
            assert.equal(node.type(), 2);
        });

        it("can bdecode buffer", function(done) {
            fs.readFile("res/debian-8.5.0-amd64-netinst.iso.torrent", (err, data) => {
                if (err) { throw err; }

                var node = lt.bdecode(data);
                assert.equal(node.type(), 1);

                done();
            });
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
        it("accepts a settings_pack", function() {
            var set = new lt.settings_pack();
            set.set_bool(lt.settings_pack.bool_types.anonymous_mode, true);

            var session = new lt.session({ settings: set });
            var sessionSettings = session.get_settings();

            assert.equal(true, sessionSettings.get_bool(lt.settings_pack.bool_types.anonymous_mode));
        });

        it("can add dht router", function() {
            var obj = new lt.session();
            obj.add_dht_router("router.bittorrent.com", 6881);
        });

        it("can add torrent", function() {
            var obj = new lt.session();
            var handle = obj.add_torrent({
                save_path: "./",
                ti: new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent")
            });

            assert.equal("debian-8.5.0-amd64-netinst.iso", handle.status().name);
        });

        it("can apply settings", function() {
            var obj = new lt.session();
            obj.apply_settings(new lt.settings_pack());
        });

        it("can load state", function() {
            var obj = new lt.session();
            obj.load_state(lt.bdecode("le"));
        });

        it("can remove torrent", function() {
            var obj = new lt.session();
            var handle = obj.add_torrent({
                save_path: "./",
                ti: new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent")
            });
            obj.remove_torrent(handle, { delete_files: true });
        });

        it("can wait for alert", function(done) {
            var obj = new lt.session();
            obj.wait_for_alert(10000, function(error, result) {
                assert.equal(result, true);
                done();
            });
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
    });

    describe("settings_pack", function() {
        it("can set bool", function() {
            var settings = new lt.settings_pack();
            settings.set_bool(lt.settings_pack.bool_types.anonymous_mode, true);
            assert.equal(true, settings.get_bool(lt.settings_pack.bool_types.anonymous_mode));
        });

        it("can set int", function() {
            var settings = new lt.settings_pack();
            settings.set_int(lt.settings_pack.int_types.proxy_port, 1337);
            assert.equal(1337, settings.get_int(lt.settings_pack.int_types.proxy_port));
        });

        it("can set string", function() {
            var settings = new lt.settings_pack();
            settings.set_str(lt.settings_pack.str_types.user_agent, "Porla");
            assert.equal("Porla", settings.get_str(lt.settings_pack.str_types.user_agent));
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
