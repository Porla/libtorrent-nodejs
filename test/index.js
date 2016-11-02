var fs = require('fs');
var lt = require('../');
var assert = require('assert');

var SegfaultHandler = require('segfault-handler');
SegfaultHandler.registerHandler();

function assertProperty(object, propertyName, testValue) {
    assert(propertyName in object, 'object does not contain property "' + propertyName + '"');
    object[propertyName] = testValue;
    assert.equal(testValue, object[propertyName]);
}

describe('libtorrent', function() {
    this.timeout(10000);

    describe("bdecode", function() {
        it("can bdecode string", function() {
            var list = lt.bdecode("li2ei3ee");
            assert.equal(3, list[1]);
        });

        it("can bdecode buffer", function(done) {
            fs.readFile("res/debian-8.5.0-amd64-netinst.iso.torrent", (err, data) => {
                if (err) { throw err; }

                var obj = lt.bdecode(data);
                assert.equal('object', typeof obj);

                done();
            });
        });

        it("throws on invalid input", function() {
            assert.throws(function() { lt.bdecode("invalid input"); });
        });
    });

    describe("bencode", function() {
        it("can encode dict", function() {
            assert.equal("de", lt.bencode({}));
        });

        it("can encode integer", function() {
            assert.equal("i2e", lt.bencode(2));
        });

        it("can encode list", function() {
            assert.equal("le", lt.bencode([]));
        });

        it("can encode string", function() {
            assert.equal("3:foo", lt.bencode("foo"));
        });
    });

    describe("create_torrent", function() {
        it("can be constructed from torrent_info", function() {
            var ti = new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent");
            var ct = new lt.create_torrent({ ti: ti });
            var entry = ct.generate();

            assert.equal(1465059745, entry['creation date']);
        });
    });

    describe("file_storage", function() {
        var storage = null;

        beforeEach(function() {
            storage = new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent").files();
        });

        afterEach(function() {
            storage = null;
        });

        it("is_valid()", function() {
            assert(storage.is_valid());
        });

        it("num_files()", () => assert(storage.num_files() > 0));
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
                flags: 0x020,
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
                flags: 0x020,
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

        it("save_state()", function() {
            var obj = new lt.session();
            var e = obj.save_state();
            assert.equal('object', typeof e);
        })
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
        it("can be constructed from a bdecoded object", function(done) {
            fs.readFile("res/debian-8.5.0-amd64-netinst.iso.torrent", (err, data) => {
                if (err) { throw err; }

                var obj = lt.bdecode(data);
                var ti = new lt.torrent_info(obj);
                assert.equal("debian-8.5.0-amd64-netinst.iso", ti.name());
                done();
            });
        });

        it("can be constructed from a path", function() {
            var ti = new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent");
            assert.equal("debian-8.5.0-amd64-netinst.iso", ti.name());
        });

        it("throws error when passed a non-existing path", function() {
            assert.throws(function() { new lt.torrent_info("non-existing path"); });
        });
    });

    describe("torrent_handle", function() {
        var session = null;
        var handle = null;

        beforeEach(function() {
            session = new lt.session();
            handle = session.add_torrent({
                flags: 0x020,
                save_path: "./",
                ti: new lt.torrent_info("res/debian-8.5.0-amd64-netinst.iso.torrent")
            });
        });

        afterEach(function() {
            session.remove_torrent(handle);
            handle = null;
            session = null;
        });

        it("get_peer_info()", function() {
            var peers = handle.get_peer_info();
            assert(peers.length >= 0);
        });

        it("status()", function() {
            assert.equal("object", typeof handle.status());
        })

        it("set_piece_deadline(1, 1000, 0)", function() {
            handle.set_piece_deadline(1, 1000, 0);
        });

        it("reset_piece_deadline(1)", function() {
            handle.reset_piece_deadline(1);
        });

        it("clear_piece_deadlines()", function() {
            handle.clear_piece_deadlines();
        });

        it("file_progress()", function() {
            assert(handle.file_progress().length > 0);
        });

        it("clear_error()", function() {
            handle.clear_error();
        });

        it("trackers()", function() {
            assert(handle.trackers().length > 0);
        });

        it("replace_trackers([{}])", function() {
            handle.replace_trackers([]);
            assert.equal(0, handle.trackers().length);
        });

        it("add_tracker({})", function() {
            var current = handle.trackers().length;
            handle.add_tracker({ url: "http://foo.com" });
            assert.equal(handle.trackers().length, current + 1);
        });

        it("add_url_seed()", function() {
            handle.add_url_seed("http://foo.com");
        });

        it("remove_url_seed()", function() {
            handle.remove_url_seed("http://foo.com");
        });

        it("url_seeds()", function() {
            assert(handle.url_seeds().length >= 0);
        });

        it("add_http_seed()", function() {
            handle.add_http_seed("http://foo.com");
        });

        it("remove_http_seed()", function() {
            handle.remove_http_seed("http://foo.com");
        });

        it("http_seeds()", function() {
            assert(handle.http_seeds().length >= 0);
        });

        it("is_valid()", function() {
            assert.equal(true, handle.is_valid());
        });

        it("pause()", function() {
            handle.pause();
        });

        it("resume()", function() {
            handle.resume();
        });

        it("stop_when_ready()", function() {
            handle.stop_when_ready(true);
        });

        it("set_upload_mode()", function() {
            handle.set_upload_mode(true);
        });

        it("set_share_mode()", function() {
            handle.set_share_mode(true);
        });

        it("flush_cache()", function() {
            handle.flush_cache();
        });

        it("apply_ip_filter()", function() {
            handle.apply_ip_filter(true);
        });

        it("force_recheck()", function() {
            handle.force_recheck();
        });

        it("save_resume_data()", function() {
            handle.save_resume_data();
        });

        it("need_save_resume_data()", function() {
            assert.equal("boolean", typeof handle.need_save_resume_data());
        });

        it("auto_managed()", function() {
            handle.auto_managed(true);
        });

        it("queue_position()", function() {
            assert.equal("number", typeof handle.queue_position());
        });

        it("queue_position_up()", function() {
            handle.queue_position_up();
        });

        it("queue_position_down()", function() {
            handle.queue_position_down();
        });

        it("queue_position_top()", function() {
            handle.queue_position_top();
        });

        it("queue_position_bottom()", function() {
            handle.queue_position_bottom();
        });

        it("torrent_file()", function() {
            assert(handle.torrent_file().name().length > 0);
        });

        it("piece_availability()", function() {
            assert(handle.piece_availability().length >= 0);
        });

        it("piece_priority(1)", function() {
            assert.equal("number", typeof handle.piece_priority(1));
        });

        it("piece_priority(1, 1)", function() {
            handle.piece_priority(1, 1);
        });

        it("prioritize_pieces([{}])", function() {
            handle.prioritize_pieces([{ index: 1, priority: 2 }]);
        });

        it("prioritize_pieces([])", function() {
            handle.prioritize_pieces([1,1,1]);
        });

        it("piece_priorities", function() {
            assert(handle.piece_priorities().length >= 0);
        });

        it("file_priority(0)", function() {
            assert.equal("number", typeof handle.file_priority(0));
        });

        it("file_priority(0, 1)", function() {
            handle.file_priority(0, 1);
        });

        it("prioritize_files([])", function() {
            handle.prioritize_files([1,1,1]);
        });

        it("file_priorities()", function() {
            assert(handle.file_priorities().length >= 0);
        });

        it("force_reannounce(1,1)", function() {
            handle.force_reannounce(1, 1);
        });

        it("force_dht_announce()", function() {
            handle.force_dht_announce();
        });

        it("scrape_tracker(1)", function() {
            handle.scrape_tracker(1);
        });

        it("set_upload_limit(1)", function() {
            handle.set_upload_limit(1);
        });

        it("upload_limit()", function() {
            assert.equal("number", typeof handle.upload_limit());
        });

        it("set_download_limit(1)", function() {
            handle.set_download_limit(1);
        });

        it("download_limit()", function() {
            assert.equal("number", typeof handle.download_limit());
        });

        it("set_sequential_download()", function() {
            handle.set_sequential_download(true);
        });

        it("connect_peer()", function() {
            handle.connect_peer([ "127.0.0.1", 6881 ]);
        });

        it("set_max_uploads()", function() {
            handle.set_max_uploads(100);
        });

        it("max_uploads()", function() {
            assert.equal("number", typeof handle.max_uploads());
        });

        it("set_max_connections()", function() {
            handle.set_max_connections(100);
        });

        it("max_connections()", function() {
            assert.equal("number", typeof handle.max_connections());
        });
    });
});
