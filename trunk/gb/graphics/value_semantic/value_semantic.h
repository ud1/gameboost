ction(fileName) {
				this.isLastRequired(fileName);
				for (var i = 0; i < this._toRun.length; i++) {
					this._toRun[i](fileName);
				}
			},
			addStrictFunction: function(newOne) {
				for (var i = 0; i < this._toRun.length; i++) {
					if (this._toRun[i].toString() === newOne.toString()) {
						return;
					}
				}
				this._toRun.push(newOne);
				this.load();
			}
		};

		/* delegate */
		(function (from, to) {
			for (var i in from) {
				if (from.hasOwnProperty(i)) {
					to[i] = from[i];
				}
			}

			return arguments.callee;
		}
			(mixin, Begun.Scripts)
			(urlUtils, Begun.Scripts)
		);
	}

	if (typeof Begun.loaderCallbacks !== 'undefined') {
		for (i = 0; i < Begun.loaderCallbacks.length; i++) { 
			Begun.loaderCallbacks[i]();
		}
	